JAR = jwayland.jar
JAVA = $(shell find src/ -name '*.java')
PROTOCOLS = $(shell find protocols/ -name '*.xml')
NATIVE_PROTOCOL_CLIENT_DIR = native/protocol/client
NATIVE_PROTOCOL_SERVER_DIR = native/protocol/server
JAVA_PROTOCOL_CLIENT_DIR = src/dev/fabillo/jwayland/protocol/client
JAVA_PROTOCOL_SERVER_DIR = src/dev/fabillo/jwayland/protocol/server
UTIL_DIR = native
BIN = native/libjwayland.so
OBJ = $(addprefix native/,clientdisplay.o serverdisplay.o simple_shm_pool.o shmbuffer.o eventloop.o protocol/interfaces.o) $(subst .c,.o,$(wildcard $(NATIVE_PROTOCOL_CLIENT_DIR)/*.c)) $(subst .c,.o,$(wildcard $(NATIVE_PROTOCOL_SERVER_DIR)/*.c))

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

scan: clean_protocols
	python3 scanner.py interfaces native/protocol $(PROTOCOLS)
	python3 scanner.py client-jni-code $(NATIVE_PROTOCOL_CLIENT_DIR) $(PROTOCOLS)
	python3 scanner.py server-jni-code $(NATIVE_PROTOCOL_SERVER_DIR) $(PROTOCOLS)
	python3 scanner.py client-java-code $(JAVA_PROTOCOL_CLIENT_DIR) $(PROTOCOLS)
	python3 scanner.py server-java-code $(JAVA_PROTOCOL_SERVER_DIR) $(PROTOCOLS)

clean:
	rm -f $(BIN) $(OBJ) $(JAR)
	rm -rf classes

clean_protocols: clean
	rm -f native/protocol/interfaces.c $(NATIVE_PROTOCOL_CLIENT_DIR)/*.c $(NATIVE_PROTOCOL_SERVER_DIR)/*.c $(JAVA_PROTOCOL_CLIENT_DIR)/*.java $(JAVA_PROTOCOL_SERVER_DIR)/*.java

.PHONY: all scan clean clean_protocols
