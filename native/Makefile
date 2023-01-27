PROTOCOL_DIR = protocol
UTIL_DIR = .
BIN = libjwayland.so
OBJ = clientdisplay.o serverdisplay.o simple_shm_pool.o $(subst .c,.o,$(wildcard $(PROTOCOL_DIR)/*.c))

ifeq ($(JAVA_HOME),)
JAVA_HOME = $(realpath $(dir $(realpath $(shell which javac)))/../ )
endif

all: $(BIN)

$(BIN): $(OBJ) $(PROTOCOL_OBJ)
	$(CC) -fPIC -shared -o $(BIN) $(OBJ) $(PROTOCOL_OBJ) -lwayland-client

clientdisplay.o: clientdisplay.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

serverdisplay.o: serverdisplay.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

simple_shm_pool.o: simple_shm_pool.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<

$(PROTOCOL_DIR)/%.o: $(PROTOCOL_DIR)/%.c $(UTIL_DIR)/util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: all clean
