# JWayland
### Wayland JNI bindings for Java

Note: This library is still experimental.
Breaking changes will happen.
You may run into SEGFAULTs, please report them.

## Features
- Client + Server bindings
- Core Wayland necessities like shared memory management are abstracted away
- Generate extensions bindings (Java and C code) with one command

## Requirements
- Python 3.10 (not tested with older versions)
- Java Development Kit
- GCC (or compatible C compiler)
- GNU Make
- Apache ant
- Wayland

## Releases
The releases provide you pre-scanned and compiled versions of the library.

The extensions are the most recent wayland-protocols.

In the case that multiple versions of an extension are available, the most stable option is chosen.

## Compiling
1. Copy the required protocol xml files (including the core `wayland.xml`!) to `protocols/`
2. Run `make scan` to generate all of the protocol-specific code
3. Run `make` to compile the library
4. Add `jwayland.jar` and `jwayland_native.jar` to your classpath
