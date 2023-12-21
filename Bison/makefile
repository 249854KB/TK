# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wno-error=unused-function

SRC_DIR = comp/
DEST_DIR = build/

# Get a list of all source files in the comp directory
SRCS = $(wildcard $(SRC_DIR)*.c)
TARGETS = $(patsubst $(SRC_DIR)%.c,$(DEST_DIR)%.o,$(SRCS))

# Main target
PROJECT_NAME = Notacja_wyrostkowa


# Default target
all: makedir flex bison update_sources bs 
bs: build link

# Make build directory if it doesn't exist already
makedir:
	mkdir -p $(DEST_DIR)

# Flex part
flex: $(SRC_DIR)lexer.c

$(SRC_DIR)lexer.c: lexer.lex
	flex -l -o $(SRC_DIR)lexer.c lexer.lex

# Bison part
bison:$(SRC_DIR)parser.c  $(SRC_DIR)parser.h

$(SRC_DIR)parser.c $(SRC_DIR)parser.h: parser.y 
	bison -v -t -d -o $(SRC_DIR)parser.c parser.y

# Updating SRCS and TARGETS
update_sources:
	$(eval SRCS = $(shell find $(SRC_DIR) -name "*.c"))
	$(eval TARGETS = $(patsubst $(SRC_DIR)%.c,$(DEST_DIR)%.o,$(SRCS)))
	@echo "New targets list $(TARGETS)"

# Build all object files
build: $(DEST_DIR)lexer.o $(DEST_DIR)parser.o $(TARGETS)


# Linker
link: $(TARGETS)
	$(CC) -o  $(PROJECT_NAME) $(addprefix $(DEST_DIR), $(notdir $(TARGETS))) -lfl


$(DEST_DIR)error.o: $(SRC_DIR)error.c $(SRC_DIR)parser.h
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)lexer.o: $(SRC_DIR)lexer.c $(SRC_DIR)parser.h
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)main.o: $(SRC_DIR)main.c $(SRC_DIR)global.h $(SRC_DIR)parser.h
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)parser.o: $(SRC_DIR)parser.c $(SRC_DIR)global.h $(SRC_DIR)parser.h
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)symbol.o: $(SRC_DIR)symbol.c $(SRC_DIR)global.h 
	$(CC) -c $(CFLAGS) $< -o $@


# Clean up generated files and executable
clean:
	rm -f $(DEST_DIR)/*.o $(PROJECT_NAME)
	rm -f $(SRC_DIR)lexer.c
	rm -f $(SRC_DIR)parser.c
	rm -f $(SRC_DIR)parser.h
	rm -f $(SRC_DIR)parser.output

# Calling the default target on empty
.PHONY: all



