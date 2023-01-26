BIN = libjwayland.so
OBJ = clientdisplay.o serverdisplay.o

ifeq ($(JAVA_HOME),)
JAVA_HOME = $(realpath $(dir $(realpath $(shell which javac)))/../ )
endif

include protocol/protocol.mk

all: $(BIN)

$(BIN): $(OBJ) $(PROTOCOL_OBJ)
	$(CC) -fPIC -shared -o $(BIN) $(OBJ) $(PROTOCOL_OBJ) -lwayland-client

clientdisplay.o: clientdisplay.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

serverdisplay.o: serverdisplay.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: all clean
