# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wno-error=unused-function

SRC_DIR = comp/
DEST_DIR = build/

# Get a list of all source files in the comp directory
SRCS = $(wildcard $(SRC_DIR)*.c)

# Main target
PROJECT_NAME = Notacja_wyrostkowa
TARGETS = $(patsubst $(SRC_DIR)%.c,$(DEST_DIR)%.o,$(SRCS))

# Default target
all: makedir flex build link

# Build rules for each source file
$(DEST_DIR)emitter.o: $(SRC_DIR)emitter.c $(SRC_DIR)global.h
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)error.o: $(SRC_DIR)error.c
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)init.o: $(SRC_DIR)init.c $(SRC_DIR)global.h
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)lexer.o: $(SRC_DIR)lexer.c
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)main.o: $(SRC_DIR)main.c $(SRC_DIR)global.h
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)parser.o: $(SRC_DIR)parser.c $(SRC_DIR)global.h
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)symbol.o: $(SRC_DIR)symbol.c $(SRC_DIR)global.h
	$(CC) -c $(CFLAGS) $< -o $@

# Linker
link: $(TARGETS)
	$(CC) -o $(PROJECT_NAME) $(addprefix $(DEST_DIR)/, $(notdir $(TARGETS))) 

# Build all object files
build: $(TARGETS)

# Make build directory if it doesn't exist already
makedir:
	mkdir -p $(DEST_DIR)

# Clean up generated files and executable
clean:
	rm -f $(DEST_DIR)/*.o $(PROJECT_NAME)

# Calling the default target on empty
.PHONY: all

flex: $(DEST_DIR)lexer.c

$(DEST_DIR)lexer.c: lexer.lex
	flex -l -o $(SRC_DIR)lexer.c lexer.lex