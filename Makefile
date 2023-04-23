CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

PARENT_DIR_NAME = $(notdir $(CURDIR))
EXECUTABLE = bin/$(PARENT_DIR_NAME)

.PHONY: all clean

all: clean $(EXECUTABLE)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

$(EXECUTABLE): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
