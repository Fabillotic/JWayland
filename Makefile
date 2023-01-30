PROTOCOL_CLIENT_DIR = native/protocol/client
PROTOCOL_SERVER_DIR = native/protocol/server
UTIL_DIR = native
BIN = native/libjwayland.so
OBJ = $(addprefix native/,clientdisplay.o serverdisplay.o simple_shm_pool.o shmbuffer.o eventloop.o protocol/interfaces.o) $(subst .c,.o,$(wildcard $(PROTOCOL_CLIENT_DIR)/*.c)) $(subst .c,.o,$(wildcard $(PROTOCOL_SERVER_DIR)/*.c))

ifeq ($(JAVA_HOME),)
JAVA_HOME = $(realpath $(dir $(realpath $(shell which javac)))/../ )
endif

all: $(BIN)

$(BIN): $(OBJ) $(PROTOCOL_OBJ)
	$(CC) -fPIC -shared -o $(BIN) $(OBJ) $(PROTOCOL_OBJ) -lwayland-client -lwayland-server

native/clientdisplay.o: native/clientdisplay.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

native/serverdisplay.o: native/serverdisplay.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

native/simple_shm_pool.o: native/simple_shm_pool.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

native/shmbuffer.o: native/shmbuffer.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

native/eventloop.o: native/eventloop.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

$(PROTOCOL_CLIENT_DIR)/%.o: $(PROTOCOL_CLIENT_DIR)/%.c $(UTIL_DIR)/util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

$(PROTOCOL_SERVER_DIR)/%.o: $(PROTOCOL_SERVER_DIR)/%.c $(UTIL_DIR)/util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

native/protocol/interfaces.o: native/protocol/interfaces.c
	$(CC) -fPIC -c -I$(UTIL_DIR) -o $@ $<

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: all clean
