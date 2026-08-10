# Compiler and flags

CC = clang
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Directories

SRC_DIR = src
OBJ_DIR = build
TARGET = emu

# Find all .c files recursively inside src/

SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')

# Convert:
# src/main.c          -> build/main.o
# src/cpu/cpu.c       -> build/cpu/cpu.o
# src/memory/memory.c -> build/memory/memory.o

OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Default target

all: $(TARGET)

# Link all object files into final program

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)

# Compile all src/*.c files, including subdirectories

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run emulator

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
