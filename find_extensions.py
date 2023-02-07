#!/bin/python3

from sys import argv
from pathlib import Path
import shutil

selection = []
extensions = []

if __name__ == "__main__":
    out_dir = "protocols"
    ext_dir = "/usr/share/wayland-protocols"
    base_dir = "/usr/share/wayland"

    out_dir = Path(out_dir)
    if not (out_dir.exists() and out_dir.is_dir()):
        print("Output directory does not exist!")
        exit()

    i = input(f"This script will delete all files in the '{out_dir.absolute()}' directory. Continue? [y/N] ")
    if not (i.lower() == "y" or i.lower() == "yes"):
        print("No confirmation given. Stopping...")
        exit()

    for x in out_dir.rglob("*.xml"):
        x.unlink(missing_ok=False)

    ext_dir = Path(ext_dir)
    if not (ext_dir.exists() and ext_dir.is_dir()):
        print("Could not find protocols directory!")
        exit()

    core = Path(base_dir) / "wayland.xml"
    if not (core.exists() and core.is_file()):
        print("Could not find wayland core protocol!")
        exit()

    shutil.copyfile(core, out_dir / "wayland.xml")

    print("Protocols:")
    fs = ext_dir.rglob("*.xml")
    for i, p in enumerate(fs):
        s = str(p.relative_to(ext_dir))
        print(f"[{i + 1}]: " + s)
        extensions.append(p)
    print()

    if len(extensions) == 0:
        print("No protocols found!")
        exit()

    print("The following selection is a space-seperated list of indexes (e.g. '1 5 3') and both-inclusive ranges (e.g. '5-10').\nNo protocols are selected by default.\nThe tokens are evaluated in the order they appear.\n'^' inverts the selection, '*' means everything")
    s = input("Select protocols: ")

    if s == "":
        print("No protocols selected!")
        exit()

    for ps in s.split(" "):
        p = None
        inverted = False
        if ps.startswith("^"):
            inverted = True
            ps = ps[1:]

        if ps == "*":
            p = (1, len(extensions))
        elif ps.count("-") == 1:
            (p1, p2) = ps.split("-")
            if not p1.isnumeric():
                print(f"Invalid selection! Could not recognize '{p1}'")
                exit()
            if not p2.isnumeric():
                print(f"Invalid selection! Could not recognize '{p2}'")
                exit()
            p1 = int(p1)
            p2 = int(p2)
            if p1 > p2:
                p = (p2, p1)
            elif p1 == p2:
                p = p1
            else:
                p = (p1, p2)
        elif ps.isnumeric():
            p = int(ps)
        else:
            print(f"Invalid selection! Could not recognize '{ps}'")
            exit()
        if type(p) is int:
            if p < 1 or p > len(extensions):
                print(f"Invalid selection! '{p}' is out of range 1-{len(extensions)}")
                exit()
            if not inverted:
                if not (p - 1) in selection:
                    selection.append(p - 1)
            else:
                if (p - 1) in selection:
                    selection.remove(p - 1)
        elif type(p) == tuple:
            if not inverted:
                for l in range(p[0] - 1, p[1]):
                    if not l in selection:
                        selection.append(l)
            else:
                for l in range(p[0] - 1, p[1]):
                    if l in selection:
                        selection.remove(l)
    print()

    if len(selection) == 0:
        print("No protocols selected!")
        exit()

    print("Selected:")
    for x in selection:
        o = extensions[x]
        c = Path(out_dir, o.name)
        print("[" + str(x + 1) + "] " + str(extensions[x]) + " -> " + str(c))

    i = input("Begin copying? [Y/n] ")
    if not (i.lower() == "" or i.lower() == "y" or i.lower() == "yes"):
        print("No confirmation given. Stopping...")
        exit()

    for x in selection:
        o = extensions[x]
        c = Path(out_dir, o.name)
        if not (o.exists() and o.is_file()):
            print("ERROR! Protocol file doesn't exist anymore!!")
            exit()
        if c.exists():
            if c.is_dir():
                print("ERROR! Output location is already a directory!")
                exit()
            elif c.is_file():
                print("File already exists! stopping...")
                exit()
        shutil.copyfile(o, c)

    print("done.")
