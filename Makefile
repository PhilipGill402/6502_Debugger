# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = build
TARGET = emu

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
ALL_SRC := $(SRC_FILES)

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Default target
all: $(TARGET)

# Link all object files into final program
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)

# Compile src/*.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test/test.c
$(OBJ_DIR)/test.o: $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build folder exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean
