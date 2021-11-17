CC=g++
CFLAGS = -Wextra -Wall -std=c++11
SOURCE_DIR = src
EXAMPLES_DIR = examples
BIN_DIR = bin

clean:
	@echo "Cleaning project"
	rm -rf $(BIN_DIR)/*

examples: example1 example2 example3

example1:
	@echo "Building example program 1"
	$(CC) $(wildcard $(EXAMPLES_DIR)/01*/*.cpp) $(wildcard $(SOURCE_DIR)/*.cpp) -o $(BIN_DIR)/01_load_bin_from_file $(CFLAGS)

example2:
	@echo "Building example program 2"
	$(CC) $(wildcard $(EXAMPLES_DIR)/02*/*.cpp) $(wildcard $(SOURCE_DIR)/*.cpp) -o $(BIN_DIR)/02_ascii_lowercase $(CFLAGS)

example3:
	@echo "Building example program 3"
	$(CC) $(wildcard $(EXAMPLES_DIR)/03*/*.cpp) $(wildcard $(SOURCE_DIR)/*.cpp) -o $(BIN_DIR)/03_conditional_branching $(CFLAGS)
