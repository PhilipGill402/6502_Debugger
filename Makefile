# Compiler and flags

CC = clang
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -Itest

# Directories

SRC_DIR = src
TEST_DIR = test
OBJ_DIR = build
TARGET = 6502_debug

# Find all .c files recursively

SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')
TEST_FILES := $(shell find $(TEST_DIR) -name '*.c')

# Convert:
# src/main.c            -> build/src/main.o
# src/cpu/cpu.c         -> build/src/cpu/cpu.o
# test/test_cpu.c       -> build/test/test_cpu.o

SRC_OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/src/%.o,$(SRC_FILES))
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/test/%.o,$(TEST_FILES))

OBJ_FILES := $(SRC_OBJ_FILES) $(TEST_OBJ_FILES)

# Default target

all: $(TARGET)

# Link everything

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)

# Compile src files

$(OBJ_DIR)/src/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files

$(OBJ_DIR)/test/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run emulator

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
