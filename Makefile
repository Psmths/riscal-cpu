CC=g++
CFLAGS = -Wextra -Wall -std=c++11
SOURCE_DIR = src
EXAMPLES_DIR = examples
BIN_DIR = bin

clean:
	@echo "Cleaning project"
	rm -rf $(BIN_DIR)/*

examples: helloworld adder

helloworld:
	@echo "Building example program 1 - helloworld.asm"
	$(CC) $(wildcard $(EXAMPLES_DIR)/01*/*.cpp) $(wildcard $(SOURCE_DIR)/*.cpp) -o $(BIN_DIR)/01_helloworld $(CFLAGS)

adder:
	@echo "Building example program 2 - my_adder.asm"
	$(CC) $(wildcard $(EXAMPLES_DIR)/02*/*.cpp) $(wildcard $(SOURCE_DIR)/*.cpp) -o $(BIN_DIR)/02_adder $(CFLAGS)
