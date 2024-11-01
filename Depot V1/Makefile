CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c99
OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(BIN_DIR)/neural_network

$(BIN_DIR)/neural_network: $(OBJ)
	$(CC) -o $@ $^ -lm  # Link with the math library

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN_DIR)/neural_network
	./$(BIN_DIR)/neural_network  # Run the compiled program

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/neural_network
