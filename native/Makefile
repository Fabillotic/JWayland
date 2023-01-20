BIN = libjwayland.so
OBJ = jwayland.o

ifeq ($(JAVA_HOME),)
JAVA_HOME = $(realpath $(dir $(realpath $(shell which javac)))/../ )
endif

all: $(BIN)
	@echo $(JAVA_HOME)

$(BIN): $(OBJ)
	$(CC) -fPIC -shared -o $@ $< -lwayland-client

jwayland.o: jwayland.c
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -o $@ $<
