PROTOCOL_CLIENT_DIR = protocol/client
PROTOCOL_SERVER_DIR = protocol/server
UTIL_DIR = .
BIN = libjwayland.so
OBJ = clientdisplay.o serverdisplay.o simple_shm_pool.o protocol/interfaces.o $(subst .c,.o,$(wildcard $(PROTOCOL_CLIENT_DIR)/*.c)) $(subst .c,.o,$(wildcard $(PROTOCOL_SERVER_DIR)/*.c))

ifeq ($(JAVA_HOME),)
JAVA_HOME = $(realpath $(dir $(realpath $(shell which javac)))/../ )
endif

all: $(BIN)

$(BIN): $(OBJ) $(PROTOCOL_OBJ)
	$(CC) -fPIC -shared -o $(BIN) $(OBJ) $(PROTOCOL_OBJ) -lwayland-client -lwayland-server

clientdisplay.o: clientdisplay.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

serverdisplay.o: serverdisplay.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

simple_shm_pool.o: simple_shm_pool.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

$(PROTOCOL_CLIENT_DIR)/%.o: $(PROTOCOL_CLIENT_DIR)/%.c $(UTIL_DIR)/util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

$(PROTOCOL_SERVER_DIR)/%.o: $(PROTOCOL_SERVER_DIR)/%.c $(UTIL_DIR)/util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

protocol/interfaces.o: protocol/interfaces.c
	$(CC) -fPIC -c -I$(UTIL_DIR) -o $@ $<

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: all clean
