# JWayland
### Wayland JNI bindings for Java

Note: This library is still experimental. It works when it works, but don't expect proper error handling yet

## Features
- Client + Server bindings
- Core Wayland necessities like shared memory management are abstracted away
- Generate extensions bindings (Java and C code) with one command

## Compiling
1. Copy the required protocol xml files (including the core `wayland.xml`!) to `protocols/`
2. Run `make scan` to generate all of the protocol-spsecific code
3. Run `make` to compile the library
4. Add the `jwayland.jar` to your classpath
5. (You will likely need to add the jni library `native/libjwayland.so` to your library path)
