JAR = jwayland.jar
NATIVE_JAR = jwayland_native.jar
SOURCE_JAR = jwayland_source.jar
JAVA = $(shell find src/ -name '*.java')
PROTOCOLS = $(shell find protocols/ -name '*.xml')
NATIVE_PROTOCOL_CLIENT_DIR = native/protocol/client
NATIVE_PROTOCOL_SERVER_DIR = native/protocol/server
JAVA_PROTOCOL_CLIENT_DIR = src/dev/fabillo/jwayland/protocol/client
JAVA_PROTOCOL_SERVER_DIR = src/dev/fabillo/jwayland/protocol/server
JAVA_PROTOCOL_ENUM_DIR = src/dev/fabillo/jwayland/protocol/enums
UTIL_DIR = native
BIN_NAME = libjwayland.so
BIN = native/$(BIN_NAME)
OBJ = $(addprefix native/,clientdisplay.o serverdisplay.o array.o resource.o client.o simple_shm_pool.o shmbuffer.o eventloop.o protocol/interfaces.o) $(subst .c,.o,$(wildcard $(NATIVE_PROTOCOL_CLIENT_DIR)/*.c)) $(subst .c,.o,$(wildcard $(NATIVE_PROTOCOL_SERVER_DIR)/*.c))

CFLAGS = -fPIC -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR)

ifeq ($(JAVA_HOME),)
JAVA_HOME = $(realpath $(dir $(realpath $(shell which javac)))/../ )
endif

all: $(JAR) $(NATIVE_JAR) $(SOURCE_JAR)

$(JAR): $(JAVA)
	ant jar

$(BIN): $(OBJ) $(PROTOCOL_OBJ)
	$(CC) -fPIC -shared -o $(BIN) $(OBJ) $(PROTOCOL_OBJ) -lwayland-client -lwayland-server

$(NATIVE_JAR): $(BIN)
	ant native_jar

$(SOURCE_JAR): $(JAVA)
	ant source_jar

$(OBJ):

protocols:
	python3 find_extensions.py

scan: clean_all
	python3 scanner.py interfaces native/protocol $(PROTOCOLS)
	python3 scanner.py client-jni-code $(NATIVE_PROTOCOL_CLIENT_DIR) $(PROTOCOLS)
	python3 scanner.py server-jni-code $(NATIVE_PROTOCOL_SERVER_DIR) $(PROTOCOLS)
	python3 scanner.py enum-java-code $(JAVA_PROTOCOL_ENUM_DIR) $(PROTOCOLS)
	python3 scanner.py client-java-code $(JAVA_PROTOCOL_CLIENT_DIR) $(PROTOCOLS)
	python3 scanner.py server-java-code $(JAVA_PROTOCOL_SERVER_DIR) $(PROTOCOLS)

clean:
	rm -f $(BIN) $(OBJ) $(JAR) $(NATIVE_JAR) $(SOURCE_JAR)
	rm -rf classes

clean_all: clean
	rm -f native/protocol/interfaces.c
	rm -f $(NATIVE_PROTOCOL_CLIENT_DIR)/*.c
	rm -f $(NATIVE_PROTOCOL_SERVER_DIR)/*.c
	rm -f $(JAVA_PROTOCOL_CLIENT_DIR)/*.java
	rm -f $(JAVA_PROTOCOL_SERVER_DIR)/*.java
	rm -f $(JAVA_PROTOCOL_ENUM_DIR)/*.java

clean-all: clean_all

.PHONY: all protocols scan clean clean_all clean-all
