import argparse
import pathlib
import xml.etree.ElementTree as ET

def main():
    parser = argparse.ArgumentParser(prog="scanner.py", description="Generate all the necessary Java and C glue code for JWayland")
    parser.add_argument("type", choices=["client-jni-code", "client-java-code", "server-jni-code", "server-java-code", "interfaces"])
    parser.add_argument("directory", type=pathlib.Path)
    parser.add_argument("xmlfile", type=pathlib.Path, nargs="+")
    arg = parser.parse_args()

    for x in arg.xmlfile:
        if not (x.exists() and x.is_file()):
            print("Invalid file: '" + str(x) + "'!")
            return

    if not (arg.directory.exists() and arg.directory.is_dir()):
        print("Invalid directory!\n")
        return

    interfaces = []
    for x in arg.xmlfile:
        tree = ET.parse(x)
        root = tree.getroot()
        if arg.type == "client-java-code":
            for e in root.findall("interface"):
                i = parse_interface(e)
                if i == None:
                    return
                j = make_java_proxy(i)
                if j == None:
                    return
                p = pathlib.Path(arg.directory, i['camel_name'] + "Proxy.java")
                f = open(p, "w")
                f.write(j)
                f.close()
        elif arg.type == "client-jni-code":
            for e in root.findall("interface"):
                i = parse_interface(e)
                if i == None:
                    return
                j = make_java_proxy(i) #Java code signature is necessary for c code
                if j == None:
                    return
                c = make_c_glue_proxy(i)
                if c == None:
                    return
                p = pathlib.Path(arg.directory, i['name'] + ".c")
                f = open(p, "w")
                f.write(c)
                f.close()
        elif arg.type == "server-java-code":
            for e in root.findall("interface"):
                i = parse_interface(e)
                if i == None:
                    return
                j = make_java_resource(i)
                if j == None:
                    return
                p = pathlib.Path(arg.directory, i['camel_name'] + "Resource.java")
                f = open(p, "w")
                f.write(j)
                f.close()
        elif arg.type == "server-jni-code":
            for e in root.findall("interface"):
                i = parse_interface(e)
                if i == None:
                    return
                j = make_java_resource(i) #Java code signature is necessary for c code
                if j == None:
                    return
                c = make_c_glue_resource(i)
                if c == None:
                    return
                p = pathlib.Path(arg.directory, i['name'] + ".c")
                f = open(p, "w")
                f.write(c)
                f.close()
        elif arg.type == "interfaces":
            for e in root.findall("interface"):
                i = parse_interface(e)
                interfaces.append(i)
        else:
            print("Invalid argument: '" + arg.type + "'!")

    if arg.type == "interfaces":
        s = make_interface_specs(interfaces)
        p = pathlib.Path(arg.directory, "interfaces.c")
        f = open(p, "w")
        f.write(s)
        f.close()

def parse_interface(interface):
    r = {"name": sanitize_name(interface.attrib["name"])}
    print(f"{r['name']}...")
    r["camel_name"] = get_camel_name(r["name"])
    r["version"] = interface.attrib["version"]
    r["requests"] = []
    for req in interface.findall("request"):
        t = {"name": sanitize_name(req.attrib["name"]), "args": []}
        #read request XML
        for arg in req.findall("arg"):
            a = {"name": arg.attrib["name"], "type": arg.attrib["type"]}
            if "interface" in arg.attrib:
                a["interface"] = arg.attrib["interface"]
            t["args"].append(a)
        t["return_proxy"] = False
        t["sun"] = False
        #Check for multiple new_ids, determine return type
        for n, arg in enumerate(t["args"]):
            if arg["type"] == "new_id":
                if t["return_proxy"]:
                    print(f"ERROR: Multiple new_ids in interface {r['name']}->{t['name']}")
                    return
                t["return_proxy"] = True
                #Sooo, Wayland really likes messing with me.
                #A new_id without a specified interface should be prefixed with a string and uint specifing the name and type of the interface
                #That's why I call it a 'sun' for the wl_message signature it generates
                if not "interface" in arg:
                    t["args"] = t["args"][:n] + [{"name": "interface_name", "type": "string"}, {"name": "interface_version", "type": "uint"}] + t["args"][n:]
                    t["sun"] = True
        #Check for duplicate names
        for n, arg in enumerate(t["args"]):
            for n2, arg2 in enumerate(t["args"]):
                if arg == arg2 and n != n2:
                    print("ERROR: duplicate argument names!!!")
                    return
        r["requests"].append(t)
    r["events"] = []
    for ev in interface.findall("event"):
        t = {"name": sanitize_name(ev.attrib["name"]), "args": []}
        for arg in ev.findall("arg"):
            a = {"name": arg.attrib["name"], "type": arg.attrib["type"]}
            if "interface" in arg.attrib:
                a["interface"] = arg.attrib["interface"]
            t["args"].append(a)
        r["events"].append(t)
    return r

def make_java_proxy(iface):
    cname = iface["camel_name"] + "Proxy"
    lname = cname + "Listener"
    d = ""
    d += "package dev.fabillo.jwayland.protocol.client;\n"
    d += "\n"
    d += "import dev.fabillo.jwayland.client.WLProxy;\n"
    d += "import dev.fabillo.jwayland.annotation.ProxyListener;\n"
    d += "import dev.fabillo.jwayland.annotation.WLEvent;\n"
    d += "import dev.fabillo.jwayland.annotation.WLRequest;\n"
    d += "\n"
    d += f"public class {cname} extends WLProxy" + " {\n"
    d += "\t\n"
    d += f"\tpublic static {cname} fromProxy(WLProxy proxy)" + " {\n"
    d += "\t\tif(proxy == null) return null;\n"
    d += f"\t\t{cname} type = new {cname}();\n"
    d += "\t\ttype.native_ptr = proxy.native_ptr;\n"
    d += "\t\treturn type;\n"
    d += "\t}\n"
    d += "\t\n"
    d += "\t@ProxyListener\n"
    d += f"\tpublic native void addListener({lname} listener);\n"
    d += "\t\n"
    for n, req in enumerate(iface["requests"]):
        if n > 0:
            d += "\t\n"
        d += "\t@WLRequest\n"
        d += "\tpublic native "
        if req["return_proxy"]:
            for arg in req["args"]:
                if arg["type"] == "new_id":
                    if "interface" in arg:
                        d += get_camel_name(arg["interface"]) + "Proxy "
                    else:
                        d += "WLProxy "
                    break
        else:
            d += "void "
        d += req["name"]
        d += "("
        for n, arg in enumerate(req["args"]):
            if arg["type"] == "new_id":
                continue
            #Check if a comma needs to be added, new_id at the start may cause issues
            if n > (1 if req["args"][0]["type"] == "new_id" else 0):
                d += ", "
            if arg["type"] in ["int", "fixed", "fd"]:
                d += "int "
            elif arg["type"] == "uint":
                d += "long "
            elif arg["type"] == "string":
                d += "String "
            elif arg["type"] == "object":
                d += "WLProxy "
            elif arg["type"] == "array":
                d += "long " #TODO: Placeholder, arrays unimplemented
            else:
                print(f"ERROR: Unrecognized argument type: '{arg['type']}'")
                return
            d += sanitize_name(arg["name"])
        d += ");\n"
    if len(iface["requests"]) > 0:
        d += "\t\n"
    d += f"\tpublic static interface {lname}" + " {\n"
    d += "\t\t\n"
    for n, ev in enumerate(iface["events"]):
        if n > 0:
            d += "\t\t\n"
        sig = "("
        d += "\t\t@WLEvent\n"
        d += f"\t\tpublic void {ev['name']}("
        for n, arg in enumerate(ev["args"]):
            if n > 0:
                d += ", "
            if arg["type"] in ["int", "uint", "fixed", "fd"]:
                d += "int "
                sig += "I"
            elif arg["type"] == "string":
                d += "String "
                sig += "Ljava/lang/String;"
            elif arg["type"] in ["object", "new_id"]:
                d += "WLProxy "
                sig += "Ldev/fabillo/jwayland/client/WLProxy;"
            elif arg["type"] == "array":
                d += "long " #TODO: Placeholder, arrays unimplemented
                sig += "J"
            else:
                print(f"ERROR: Unrecognized argument type: '{arg['type']}'")
                return
            d += sanitize_name(arg["name"])
        d += ");\n"
        sig += ")V"
        ev["signature"] = sig
    if len(iface["events"]) > 0:
        d += "\t\t\n"
    d += "\t}\n"
    d += "\t\n"
    d += "\tstatic {\n"
    d += '\t\tSystem.loadLibrary("jwayland");\n'
    d += "\t}\n"
    d += "\t\n"
    d += "}\n"
    return d

def make_java_resource(iface):
    cname = iface["camel_name"] + "Resource"
    lname = cname + "Listener"
    d = ""
    d += "package dev.fabillo.jwayland.protocol.server;\n"
    d += "\n"
    d += "import dev.fabillo.jwayland.server.WLResource;\n"
    d += "import dev.fabillo.jwayland.annotation.ResourceListener;\n"
    d += "import dev.fabillo.jwayland.annotation.WLEvent;\n"
    d += "import dev.fabillo.jwayland.annotation.WLRequest;\n"
    d += "\n"
    d += f"public class {cname} extends WLResource" + " {\n"
    d += "\t\n"
    d += f"\tpublic static {cname} fromResource(WLResource resource)" + " {\n"
    d += "\t\tif(resource == null) return null;\n"
    d += f"\t\t{cname} type = new {cname}();\n"
    d += "\t\ttype.native_ptr = resource.native_ptr;\n"
    d += "\t\treturn type;\n"
    d += "\t}\n"
    d += "\t\n"
    d += "\t@ResourceListener\n"
    d += f"\tpublic native void addListener({lname} listener);\n"
    d += "\t\n"
    for n, ev in enumerate(iface["events"]):
        if n > 0:
            d += "\t\n"
        d += "\t@WLEvent\n"
        d += "\tpublic native void "
        d += ev["name"]
        d += "("
        for n, arg in enumerate(ev["args"]):
            if n > 0:
                d += ", "
            if arg["type"] in ["int", "fixed", "fd", "new_id"]:
                d += "int "
            elif arg["type"] == "uint":
                d += "long "
            elif arg["type"] == "string":
                d += "String "
            elif arg["type"] == "object":
                d += "WLResource "
            elif arg["type"] == "array":
                d += "long " #TODO: Placeholder, arrays unimplemented
            else:
                print(f"ERROR: Unrecognized argument type: '{arg['type']}'")
                return
            d += sanitize_name(arg["name"])
        d += ");\n"
    if len(iface["events"]) > 0:
        d += "\t\n"
    d += f"\tpublic static interface {lname}" + " {\n"
    d += "\t\t\n"
    for n, req in enumerate(iface["requests"]):
        if n > 0:
            d += "\t\t\n"
        sig = "("
        d += "\t\t@WLRequest\n"
        d += f"\t\tpublic void {req['name']}("
        for n, arg in enumerate(req["args"]):
            if n > 0:
                d += ", "
            if arg["type"] in ["int", "uint", "fixed", "fd", "new_id"]:
                d += "int "
                sig += "I"
            elif arg["type"] == "string":
                d += "String "
                sig += "Ljava/lang/String;"
            elif arg["type"] == "object":
                d += "WLResource "
                sig += "Ldev/fabillo/jwayland/server/WLResource;"
            elif arg["type"] == "array":
                d += "long " #TODO: Placeholder, arrays unimplemented
                sig += "J"
            else:
                print(f"ERROR: Unrecognized argument type: '{arg['type']}'")
                return
            d += sanitize_name(arg["name"])
        d += ");\n"
        sig += ")V"
        req["signature"] = sig
    if len(iface["events"]) > 0:
        d += "\t\t\n"
    d += "\t}\n"
    d += "\t\n"
    d += "\tstatic {\n"
    d += '\t\tSystem.loadLibrary("jwayland");\n'
    d += "\t}\n"
    d += "\t\n"
    d += "}\n"
    return d

def make_c_glue_proxy(iface):
    cname = iface["camel_name"] + "Proxy"
    d = ""
    d += "#include <jni.h>\n"
    d += "#include <stdio.h>\n"
    d += "#include <stdint.h>\n"
    d += "#include <wayland-client-core.h>\n"
    d += '#include "interfaces.h"\n'
    d += '#include "util.h"\n'
    d += "\n"
    for opcode, req in enumerate(iface["requests"]):
        if opcode > 0:
            d += '\n'
        d += "JNIEXPORT "
        d += "jobject " if req["return_proxy"] else "void "
        d += "JNICALL "
        d += "Java_dev_fabillo_jwayland_protocol_client_"
        d += cname
        d += "_"
        d += req["name"].replace("_", "_1")
        d += "(JNIEnv *env, jobject obj"
        for arg in req["args"]:
            if arg["type"] == "new_id":
                continue
            d += ", "
            if arg["type"] in ["int", "fixed", "fd"]:
                d += "jint "
            elif arg["type"] == "uint":
                d += "jlong "
            elif arg["type"] == "string":
                d += "jstring "
            elif arg["type"] == "object":
                d += "jobject "
            elif arg["type"] == "array":
                d += "jlong " #TODO: Placeholder, arrays unimplemented
            else:
                print(f"ERROR: Unrecognized argument type: '{arg['type']}'")
                return
            d += sanitize_name(arg["name"])
        d += ") {\n"
        d += '\tjclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/client/WLProxy");\n'
        d += '\tjfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");\n'
        iname = None
        if req["return_proxy"]:
            for arg in req["args"]:
                if arg["type"] == "new_id":
                    if "interface" in arg:
                        iname = get_camel_name(arg["interface"]) + "Proxy"
                        d += f'\tjclass {iname}_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/client/{iname}");\n'
                        d += f'\tjfieldID {iname}_native_ptr = (*env)->GetFieldID(env, {iname}_class, "native_ptr", "J");\n'
                    else:
                        iname = "WLProxy"
                    d += f'\tjmethodID {iname}_init = (*env)->GetMethodID(env, {iname}_class, "<init>", "()V");\n'
                    break
        d += '\n'
        d += '\tstruct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);\n'
        if req["return_proxy"]:
            d += '\tconst struct wl_interface *inf = get_interface_by_name('
            if req["sun"]:
                d += '(*env)->GetStringUTFChars(env, '
                d += 'interface_name' #argument for interface name
                d += ', NULL)'
            else:
                for n, arg in enumerate(req["args"]):
                    if arg["type"] == "new_id":
                        d += '"' + arg["interface"] + '"'
                        break
                else:
                    print("ERROR: Failed to find new_id argument interface name!")
                    return
            d += ');\n'
            d += '\tif(!inf) return NULL;\n'
            d += '\tstruct wl_proxy *nproxy = wl_proxy_marshal_constructor(wproxy, '
            d += str(opcode)
            d += ", inf"
            for arg in req["args"]:
                d += ', '
                if arg["type"] in ["int", "fixed", "fd"]:
                    d += '(int32_t) ' + sanitize_name(arg["name"])
                elif arg["type"] == "uint":
                    d += '(uint32_t) ' + sanitize_name(arg["name"])
                elif arg["type"] == "string":
                    d += '(*env)->GetStringUTFChars(env, ' + sanitize_name(arg["name"]) + ', NULL)'
                elif arg["type"] == "object":
                    d += '(struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, ' + sanitize_name(arg["name"]) + ', WLProxy_native_ptr)'
                elif arg["type"] == "array":
                    d += '(struct wl_array*)(intptr_t) ' + sanitize_name(arg["name"])
                elif arg["type"] == "new_id":
                    d += '(uint32_t) 0'
                else:
                    print(f"ERROR: Unrecognized argument type: '{arg['type']}'")
                    return
            d += ');\n';
            d += '\tif(!nproxy) return NULL;\n'
            d += f'\tjobject prox = (*env)->NewObject(env, {iname}_class, {iname}_init);\n'
            d += f'\t(*env)->SetLongField(env, prox, {iname}_native_ptr, (jlong)(intptr_t)nproxy);\n'
            d += '\treturn prox;\n'
        else:
            d += '\twl_proxy_marshal(wproxy, '
            d += str(opcode)
            for arg in req["args"]:
                d += ', '
                if arg["type"] in ["int", "fixed", "fd"]:
                    d += '(int32_t) ' + sanitize_name(arg["name"])
                elif arg["type"] == "uint":
                    d += '(uint32_t) ' + sanitize_name(arg["name"])
                elif arg["type"] == "string":
                    d += '(*env)->GetStringUTFChars(env, ' + sanitize_name(arg["name"]) + ', NULL)'
                elif arg["type"] == "object":
                    d += '(struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, ' + sanitize_name(arg["name"]) + ', WLProxy_native_ptr)'
                elif arg["type"] == "array":
                    d += '(struct wl_array*)(intptr_t) ' + sanitize_name(arg["name"])
                else:
                    print(f"ERROR: Unrecognized argument type: '{arg['type']}'")
                    return
            d += ');\n';
        d += "}\n"
    d += "\n"

    dispatcher = iface["name"] + "_proxy_dispatcher"
    lname = cname + "Listener"

    d += 'int ' + dispatcher + '(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {\n'
    d += '\tstruct wl_proxy *proxy = (struct wl_proxy*) target;\n'
    d += '\tvoid* user_data = wl_proxy_get_user_data(proxy);\n'
    d += '\tJNIEnv *env = *(JNIEnv**) user_data;\n'
    d += '\tjobject listener = (jobject) implementation;\n'
    d += '\n'
    d += '\tjclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/client/' + cname + '$' + lname + '");\n'

    for ev in iface["events"]:
        d += '\tjmethodID mListener_' + ev["name"] + ' = '
        d += '(*env)->GetMethodID(env, listener_class, "' + ev["name"] + '", '
        d += '"' + ev["signature"] + '");\n'

    d += '\n'
    d += '\tjvalue *values;\n'
    d += '\tchar *sig;\n'
    d += '\n'
    d += '\targuments_to_java(env, msg, args, &sig, &values);\n'

    d += '\tswitch(opcode) {\n'

    for n, ev in enumerate(iface["events"]):
        d += f'\t\tcase {n}: (*env)->CallVoidMethodA(env, listener, mListener_{ev["name"]}, values); break;\n'

    d += '\t\tdefault: break;\n'
    d += '\t}\n'

    d += '\n'
    d += '\treturn 0;\n'

    d += '}\n'
    d += '\n'

    d += 'JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_client_'
    d += cname
    d += '_addListener(JNIEnv *env, jobject obj, jobject listener) {\n'
    d += '\tjclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/client/WLProxy");\n'
    d += '\tjfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");\n'
    d += '\tjmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");\n'
    d += "\n"
    d += "\tjobject listener_ref = (*env)->NewGlobalRef(env, listener);\n"
    d += "\n"
    d += '\tstruct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);\n'
    d += '\tJNIEnv **data = malloc(sizeof(JNIEnv*));\n'
    d += '\t*data = env;\n'
    d += '\twl_proxy_add_dispatcher(wproxy, '
    d += dispatcher
    d += ', listener_ref, data);\n'
    d += "}\n"
    return d

def make_c_glue_resource(iface):
    cname = iface["camel_name"] + "Resource"
    d = ""
    d += "#include <jni.h>\n"
    d += "#include <stdio.h>\n"
    d += "#include <stdint.h>\n"
    d += "#include <wayland-server-core.h>\n"
    d += '#include "interfaces.h"\n'
    d += '#include "util.h"\n'
    d += "\n"
    for opcode, ev in enumerate(iface["events"]):
        if opcode > 0:
            d += '\n'
        d += "JNIEXPORT void JNICALL "
        d += "Java_dev_fabillo_jwayland_protocol_server_"
        d += cname
        d += "_"
        d += ev["name"].replace("_", "_1")
        d += "(JNIEnv *env, jobject obj"
        for arg in ev["args"]:
            d += ", "
            if arg["type"] in ["int", "fixed", "fd", "new_id"]:
                d += "jint "
            elif arg["type"] == "uint":
                d += "jlong "
            elif arg["type"] == "string":
                d += "jstring "
            elif arg["type"] == "object":
                d += "jobject "
            elif arg["type"] == "array":
                d += "jlong " #TODO: Placeholder, arrays unimplemented
            else:
                print(f"ERROR: Unrecognized argument type: '{arg['type']}'")
                return
            d += sanitize_name(arg["name"])
        d += ") {\n"
        d += '\tjclass WLResource_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLResource");\n'
        d += '\tjfieldID WLResource_native_ptr = (*env)->GetFieldID(env, WLResource_class, "native_ptr", "J");\n'
        d += '\n'
        d += '\tstruct wl_resource *wresource = (struct wl_resource*)(intptr_t)(*env)->GetLongField(env, obj, WLResource_native_ptr);\n'
        d += '\twl_resource_post_event(wresource, '
        d += str(opcode)
        for arg in ev["args"]:
            d += ', '
            if arg["type"] in ["int", "fixed", "fd", "new_id"]:
                d += '(int32_t) ' + sanitize_name(arg["name"])
            elif arg["type"] == "uint":
                d += '(uint32_t) ' + sanitize_name(arg["name"])
            elif arg["type"] == "string":
                d += '(*env)->GetStringUTFChars(env, ' + sanitize_name(arg["name"]) + ', NULL)'
            elif arg["type"] == "object":
                d += '(struct wl_resource*)(intptr_t)(*env)->GetLongField(env, ' + sanitize_name(arg["name"]) + ', WLResource_native_ptr)'
            elif arg["type"] == "array":
                d += '(struct wl_array*)(intptr_t) ' + sanitize_name(arg["name"])
            else:
                print(f"ERROR: Unrecognized argument type: '{arg['type']}'")
                return
        d += ');\n';
        d += "}\n"
    d += "\n"

    dispatcher = iface["name"] + "_resource_dispatcher"
    lname = cname + "Listener"

    d += 'int ' + dispatcher + '(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {\n'
    d += '\tstruct wl_resource *resource = (struct wl_resource*) target;\n'
    d += '\tvoid* user_data = wl_resource_get_user_data(resource);\n'
    d += '\tJNIEnv *env = *(JNIEnv**) user_data;\n'
    d += '\tjobject listener = (jobject) implementation;\n'
    d += '\n'
    d += '\tjclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/server/' + cname + '$' + lname + '");\n'

    for req in iface["requests"]:
        d += '\tjmethodID mListener_' + req["name"] + ' = '
        d += '(*env)->GetMethodID(env, listener_class, "' + req["name"] + '", '
        d += '"' + req["signature"] + '");\n'

    d += '\n'
    d += '\tjvalue *values;\n'
    d += '\tchar *sig;\n'
    d += '\n'
    d += '\targuments_to_java(env, msg, args, &sig, &values);\n'

    d += '\tswitch(opcode) {\n'

    for n, req in enumerate(iface["requests"]):
        d += f'\t\tcase {n}: (*env)->CallVoidMethodA(env, listener, mListener_{req["name"]}, values); break;\n'

    d += '\t\tdefault: break;\n'
    d += '\t}\n'

    d += '\n'
    d += '\treturn 0;\n'

    d += '}\n'
    d += '\n'

    d += 'JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_server_'
    d += cname
    d += '_addListener(JNIEnv *env, jobject obj, jobject listener) {\n'
    d += '\tjclass WLResource_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLResource");\n'
    d += '\tjfieldID WLResource_native_ptr = (*env)->GetFieldID(env, WLResource_class, "native_ptr", "J");\n'
    d += '\tjmethodID WLResource_init = (*env)->GetMethodID(env, WLResource_class, "<init>", "()V");\n'
    d += "\n"
    d += "\tjobject listener_ref = (*env)->NewGlobalRef(env, listener);\n"
    d += "\n"
    d += '\tstruct wl_resource *wresource = (struct wl_resource*)(intptr_t)(*env)->GetLongField(env, obj, WLResource_native_ptr);\n'
    d += '\tJNIEnv **data = malloc(sizeof(JNIEnv*));\n'
    d += '\t*data = env;\n'
    d += '\twl_resource_set_dispatcher(wresource, '
    d += dispatcher
    d += ', listener_ref, data, NULL);\n'
    d += "}\n"
    return d

def make_interface_specs(interfaces):
    d = ""
    d += '#include <stdio.h>\n'
    d += '#include <string.h>\n'
    d += '#include <wayland-client-core.h>\n'
    d += '#include "interfaces.h"\n'
    d += '\n'

    for iface in interfaces:
        d += 'struct wl_interface ' + iface["name"] + '_interface;\n'
    d += '\n'

    d += 'struct wl_interface *interfaces[] = {\n'
    for iface in interfaces:
        d += '\t&' + iface["name"] + '_interface,\n'
    d += '};\n'

    d += '\n'

    d += 'struct wl_interface *get_interface_by_name(const char *name) {\n'
    d += '\tint i;\n'
    d += '\n'
    d += '\tfor(i = 0; i < sizeof(interfaces) / sizeof(intptr_t); i++) {\n'
    d += '\t\tif(!strcmp(interfaces[i]->name, name)) {\n'
    d += '\t\t\treturn interfaces[i];\n'
    d += '\t\t}\n'
    d += '\t}\n'
    d += '\treturn NULL;\n'
    d += '}\n'

    for iface in interfaces:
        d += make_interface_definition(iface)

    return d

def make_interface_definition(iface):
    d = "\n\n"

    d += 'struct wl_message ' + iface["name"] + '_requests[] = {\n'
    for n, req in enumerate(iface["requests"]):
        d += '\t{"' + req["name"] + '", "'
        for arg in req["args"]:
            if arg["type"] == "int":
                d += 'i'
            elif arg["type"] == "uint":
                d += 'u'
            elif arg["type"] == "fixed":
                d += 'f'
            elif arg["type"] == "string":
                d += 's'
            elif arg["type"] == "object":
                d += 'o'
            elif arg["type"] == "new_id":
                d += 'n'
            elif arg["type"] == "array":
                d += 'a'
            elif arg["type"] == "fd":
                d += 'h'
            else:
                print(f'ERROR! Unknown argument type: "{arg["type"]}"')
                return
        d += '", (const struct wl_interface**)(struct wl_interface*[]) {'
        for n2, arg in enumerate(req["args"]):
            if n2 > 0:
                d += ', '
            if arg["type"] in ["int", "uint", "fixed", "string", "array", "fd"]:
                d += 'NULL'
            elif arg["type"] in ["object", "new_id"]:
                if not "interface" in arg:
                    d += 'NULL'
                else:
                    d += '&' + arg["interface"] + '_interface'
            else:
                print(f'ERROR! Unknown argument type: "{arg["type"]}"')
                return
        d += '}}'
        if n < len(iface["requests"]) - 1:
            d += ','
        d += '\n'
    d += '};\n'
    d += '\n'

    d += 'struct wl_message ' + iface["name"] + '_events[] = {\n'
    for n, ev in enumerate(iface["events"]):
        d += '\t{"' + ev["name"] + '", "'
        for arg in ev["args"]:
            if arg["type"] == "int":
                d += 'i'
            elif arg["type"] == "uint":
                d += 'u'
            elif arg["type"] == "fixed":
                d += 'f'
            elif arg["type"] == "string":
                d += 's'
            elif arg["type"] == "object":
                d += 'o'
            elif arg["type"] == "new_id":
                d += 'n'
            elif arg["type"] == "array":
                d += 'a'
            elif arg["type"] == "fd":
                d += 'h'
            else:
                print(f'ERROR! Unknown argument type: "{arg["type"]}"')
                return
        d += '", (const struct wl_interface**)(struct wl_interface*[]) {'
        for n2, arg in enumerate(ev["args"]):
            if n2 > 0:
                d += ', '
            if arg["type"] in ["int", "uint", "fixed", "string", "array", "fd"]:
                d += 'NULL'
            elif arg["type"] in ["object", "new_id"]:
                if not "interface" in arg:
                    d += 'NULL'
                else:
                    d += '&' + arg["interface"] + '_interface'
            else:
                print(f'ERROR! Unknown argument type: "{arg["type"]}"')
                return
        d += '}}'
        if n < len(iface["events"]) - 1:
            d += ','
        d += '\n'
    d += '};\n'
    d += '\n'

    d += 'struct wl_interface ' + iface["name"] + '_interface = {\n'
    d += '\t"' + iface["name"] + '", ' + str(iface["version"]) + ',\n'
    d += '\t' + str(len(iface["requests"])) + ', ' + iface["name"] + '_requests,\n'
    d += '\t' + str(len(iface["events"])) + ', ' + iface["name"] + '_events\n'
    d += '};\n'

    return d

def sanitize_name(name):
    if name == "interface":
        return "iface"
    elif name == "class":
        return "clazz"
    elif name == "import":
        return "imprt"
    elif name == "native":
        return "nativ"
    return name

def get_camel_name(name):
    camel_name = ""
    first_underscore = False
    for n, c in enumerate(name):
        if c != "_":
            if name[n - 1] == "_":
                first_underscore = True
                camel_name += c.upper()
            elif not first_underscore:
                camel_name += c.upper()
            else:
                camel_name += c
    return camel_name

if __name__ == "__main__":
    main()
