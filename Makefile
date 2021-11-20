CC=g++
CFLAGS = -Wextra -Wall -std=c++11
SOURCE_DIR = src
EXAMPLES_DIR = examples
BIN_DIR = bin
MD = mkdir -p

clean:
	@echo "Cleaning project"
	rm -rf $(BIN_DIR)

examples: helloworld adder xor_cipher

helloworld:
	@echo "Building example program 1 - helloworld.asm"
	$(MD) $(BIN_DIR)
	$(CC) $(wildcard $(EXAMPLES_DIR)/01*/*.cpp) $(wildcard $(SOURCE_DIR)/*.cpp) -o $(BIN_DIR)/01_helloworld $(CFLAGS)

adder:
	@echo "Building example program 2 - my_adder.asm"
	$(MD) $(BIN_DIR)
	$(CC) $(wildcard $(EXAMPLES_DIR)/02*/*.cpp) $(wildcard $(SOURCE_DIR)/*.cpp) -o $(BIN_DIR)/02_adder $(CFLAGS)

xor_cipher:
	@echo "Building example program 2 - my_adder.asm"
	$(MD) $(BIN_DIR)
	$(CC) $(wildcard $(EXAMPLES_DIR)/03*/*.cpp) $(wildcard $(SOURCE_DIR)/*.cpp) -o $(BIN_DIR)/03_xor_cipher $(CFLAGS)

test:
	./$(BIN_DIR)/01_helloworld
	./$(BIN_DIR)/02_adder
	./$(BIN_DIR)/03_xor_cipher
