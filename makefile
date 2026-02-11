# Makefile for Arbitrary Precision Calculator
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = calculator

# Source files
SOURCES = main.c \
          main_helpers.c \
          addition.c \
          subtraction.c \
          multiplication.c \
          division.c \
          insert_at_first.c \
          insert_at_last.c \
          free_list.c \
          parse_operands.c \
          compare.c \
          is_negative.c \
          validate_number.c \
          remove_dot.c \
          decimal_utils.c

# Object files (automatically generated from source files)
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build successful! Run with: ./$(TARGET) <num1> <operator> <num2>"

# Compile source files to object files
%.o: %.c apc.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean successful!"

# Rebuild everything
rebuild: clean all

# Run with test case
test: $(TARGET)
	@echo "Testing addition: 123.45 + 67.89"
	./$(TARGET) 123.45 + 67.89
	@echo "\nTesting subtraction: 100.5 - 45.25"
	./$(TARGET) 100.5 - 45.25
	@echo "\nTesting multiplication: 12.5 x 4.2"
	./$(TARGET) 12.5 x 4.2
	@echo "\nTesting Division: 1.5 / 0.5"
	/.$(TARGET) 1.5 / 0.5

# Help target
help:
	@echo "Available targets:"
	@echo "  make           - Build the calculator"
	@echo "  make clean     - Remove build artifacts"
	@echo "  make rebuild   - Clean and rebuild"
	@echo "  make test      - Run test cases"
	@echo "  make help      - Show this help message"

.PHONY: all clean rebuild test help