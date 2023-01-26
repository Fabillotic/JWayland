UTIL_DIR = .
PROTOCOL_DIR = protocol
PROTOCOL_OBJ = $(addprefix $(PROTOCOL_DIR)/,interfaces.o wl_display.o wl_callback.o wl_registry.o wp_single_pixel_buffer_manager_v1.o wl_buffer.o)

ifeq ($(JAVA_HOME),)
JAVA_HOME = $(realpath $(dir $(realpath $(shell which javac)))/../ )
endif

all: $(PROTOCOL_OBJ)

$(PROTOCOL_DIR)/%.o: $(PROTOCOL_DIR)/%.c $(UTIL_DIR)/util.h
	$(CC) -fPIC -c -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(UTIL_DIR) -o $@ $<

