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
        parse_interface(i)

def parse_interface(interface):
    r = {"name": interface.attrib["name"]}
    print(f"\n{r['name']}")
    r["camel_name"] = ""
    for n, c in enumerate(r["name"]):
        if n == 0:
            r["camel_name"] += c.upper()
        elif c != "_":
            if r["name"][n - 1] == "_":
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

if __name__ == "__main__":
    main()
