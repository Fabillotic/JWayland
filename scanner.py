from sys import argv
import xml.etree.ElementTree as ET

def main():
    if not len(argv) > 1:
        print("scanner.py: [xml file]")
        exit()
    tree = ET.parse(argv[1])
    root = tree.getroot()
    for i in root.findall("interface"):
        #if i.attrib["name"] == "wl_buffer":
        i = parse_interface(i)
        if i == None:
            return
        j = make_java_proxy(i)
        if j == None:
            return
        print(j)
        c = make_c_glue(i)
        if c == None:
            return
        print(c)
        #f = open(i["camel_name"] + ".java.test", "w")
        #f.write(j)
        #f.close()

def parse_interface(interface):
    r = {"name": interface.attrib["name"]}
    print(f"\n{r['name']}")
    r["camel_name"] = ""
    first_underscore = False
    for n, c in enumerate(r["name"]):
        if c != "_":
            if r["name"][n - 1] == "_":
                first_underscore = True
                r["camel_name"] += c.upper()
            elif not first_underscore:
                r["camel_name"] += c.upper()
            else:
                r["camel_name"] += c
    r["requests"] = []
    for req in interface.findall("request"):
        t = {"name": req.attrib["name"], "args": []}
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
                    print("SUN!")
                    t["args"] = t["args"][:n] + [{"name": "interface_name", "type": "string"}, {"name": "interface_version", "type": "uint"}] + t["args"][n:]
                    t["sun"] = True
        #Check for duplicate names
        for n, arg in enumerate(t["args"]):
            for n2, arg2 in enumerate(t["args"]):
                if arg == arg2 and n != n2:
                    print("ERROR: duplicate argument names!!!")
                    return
        r["requests"].append(t)
        print(f"request: {t}")
    r["events"] = []
    for ev in interface.findall("event"):
        t = {"name": ev.attrib["name"], "args": []}
        for arg in ev.findall("arg"):
            a = {"name": arg.attrib["name"], "type": arg.attrib["type"]}
            if "interface" in arg.attrib:
                a["interface"] = arg.attrib["interface"]
            t["args"].append(a)
        r["events"].append(t)
        print(f"event: {t}")
    return r

def make_java_proxy(iface):
    cname = iface["camel_name"]
    lname = cname + "Listener"
    d = ""
    d += "package dev.fabillo.jwayland.protocol;\n"
    d += "\n"
    d += "import dev.fabillo.jwayland.WLProxy;\n"
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
        d += "WLProxy " if req["return_proxy"] else "void "
        d += req["name"]
        d += "("
        for n, arg in enumerate(req["args"]):
            if arg["type"] == "new_id":
                continue
            #Check if a comma needs to be added, new_id at the start may cause issues
            if n > (1 if req["args"][0]["type"] == "new_id" else 0):
                d += ", "
            if arg["type"] in ["int", "uint", "fixed", "fd"]:
                d += "int "
            elif arg["type"] == "string":
                d += "String "
            elif arg["type"] == "object":
                d += "WLProxy "
            elif arg["type"] == "array":
                d += "int " #TODO: Placeholder, arrays unimplemented
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
        d += "\t\t@WLEvent\n"
        d += f"\t\tpublic void {ev['name']}("
        for n, arg in enumerate(ev["args"]):
            if n > 0:
                d += ", "
            if arg["type"] in ["int", "uint", "fixed", "fd"]:
                d += "int "
            elif arg["type"] == "string":
                d += "String "
            elif arg["type"] in ["object", "new_id"]:
                d += "WLProxy "
            elif arg["type"] == "array":
                d += "int " #TODO: Placeholder, arrays unimplemented
            else:
                print(f"ERROR: Unrecognized argument type: '{arg['type']}'")
                return
            d += sanitize_name(arg["name"])
        d += ");\n"
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

def make_c_glue(iface):
    cname = iface["camel_name"]
    d = ""
    d += "#include <jni.h>\n"
    d += "#include <stdio.h>\n"
    d += "#include <stdint.h>\n"
    d += "#include <wayland-client-core.h>\n"
    d += '#include "interfaces.h"\n'
    d += '#include "util.h"\n'
    d += "\n"
    for n, req in enumerate(iface["requests"]):
        d += "JNIEXPORT "
        d += "jobject " if req["return_proxy"] else "void "
        d += "JNICALL "
        d += "Java_dev_fabillo_jwayland_protocol_"
        d += cname
        d += "_"
        d += req["name"].replace("_", "_1")
        d += "(JNIEnv *env, jobject obj"
        for arg in req["args"]:
            if arg["type"] == "new_id":
                continue
            d += ", "
            if arg["type"] in ["int", "uint", "fixed", "fd"]:
                d += "jint "
            elif arg["type"] == "string":
                d += "jstring "
            elif arg["type"] == "object":
                d += "jobject "
            elif arg["type"] == "array":
                d += "jint " #TODO: Placeholder, arrays unimplemented
            else:
                print(f"ERROR: Unrecognized argument type: '{arg['type']}'")
                return
            d += sanitize_name(arg["name"])
        d += ") {"
        d += "}\n"
    return d

def sanitize_name(name):
    if name == "interface":
        return "iface"
    return name

if __name__ == "__main__":
    main()
