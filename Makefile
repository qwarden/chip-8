CC = gcc
CFLAGS = -Wall -Wextra `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

PARENT_DIR_NAME = $(notdir $(CURDIR))
EXECUTABLE = bin/$(PARENT_DIR_NAME)

ifeq ($(DEBUG), 1)
    CFLAGS += -g
endif

.PHONY: all clean

all: $(EXECUTABLE)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

$(EXECUTABLE): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -rf $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
