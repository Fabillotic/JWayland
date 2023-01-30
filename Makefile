JAR = jwayland.jar
JAVA = $(shell find src/ -name '*.java')
PROTOCOL_CLIENT_DIR = native/protocol/client
PROTOCOL_SERVER_DIR = native/protocol/server
UTIL_DIR = native
BIN = native/libjwayland.so
OBJ = $(addprefix native/,clientdisplay.o serverdisplay.o simple_shm_pool.o shmbuffer.o eventloop.o protocol/interfaces.o) $(subst .c,.o,$(wildcard $(PROTOCOL_CLIENT_DIR)/*.c)) $(subst .c,.o,$(wildcard $(PROTOCOL_SERVER_DIR)/*.c))

CFLAGS = -fPIC -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR)

ifeq ($(JAVA_HOME),)
JAVA_HOME = $(realpath $(dir $(realpath $(shell which javac)))/../ )
endif

all: $(JAR)

$(JAR): $(BIN) $(JAVA)
	ant jar

$(BIN): $(OBJ) $(PROTOCOL_OBJ)
	$(CC) -fPIC -shared -o $(BIN) $(OBJ) $(PROTOCOL_OBJ) -lwayland-client -lwayland-server

$(OBJ):

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: all clean
