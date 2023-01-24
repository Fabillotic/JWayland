BIN = libjwayland.so
OBJ = clientdisplay.o interfaces.o wl_display.o wl_callback.o wl_registry.o wp_single_pixel_buffer_manager_v1.o wl_buffer.o

ifeq ($(JAVA_HOME),)
JAVA_HOME = $(realpath $(dir $(realpath $(shell which javac)))/../ )
endif

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -fPIC -shared -o $(BIN) $(OBJ) -lwayland-client

clientdisplay.o: clientdisplay.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

interfaces.o: interfaces.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

wl_display.o: wl_display.c util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

wl_callback.o: wl_callback.c util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

wl_registry.o: wl_registry.c util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

wp_single_pixel_buffer_manager_v1.o: wp_single_pixel_buffer_manager_v1.c util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

wl_buffer.o: wl_buffer.c util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

.PHONY: all
