BIN = libjwayland.so
OBJ = clientdisplay.o interfaces.o proxy.o wldisplay.o wlcallback.o wlregistry.o

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

proxy.o: proxy.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

wldisplay.o: wldisplay.c util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

wlcallback.o: wlcallback.c util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

wlregistry.o: wlregistry.c util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

.PHONY: all
