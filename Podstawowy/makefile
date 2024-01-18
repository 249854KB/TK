# Compiler and flags
CC = g++
CFLAGS = -Wall -Werror -Wno-error=unused-function

SRC_DIR = comp/
DEST_DIR = build/

# Get a list of all source files in the comp directory
SRCS = $(wildcard $(SRC_DIR)*.cpp)
TARGETS = $(patsubst $(SRC_DIR)%.cpp,$(DEST_DIR)%.o,$(SRCS))

# Main target
PROJECT_NAME = Komp_podstawowy


# Default target
all: makedir bison flex update_sources bs 
bs: build link

# Make build directory if it doesn't exist already
makedir:
	mkdir -p $(DEST_DIR)

# Flex part
flex: $(SRC_DIR)lexer.cpp

$(SRC_DIR)lexer.cpp: lexer.lex
	flex -l -o $(SRC_DIR)lexer.cpp lexer.lex

# Bison part
bison:$(SRC_DIR)parser.cpp  $(SRC_DIR)parser.hpp

$(SRC_DIR)parser.cpp $(SRC_DIR)parser.hpp: parser.y 
	bison -v -t -d -o $(SRC_DIR)parser.cpp parser.y

# Updating SRCS and TARGETS
update_sources:
	$(eval SRCS = $(shell find $(SRC_DIR) -name "*.cpp"))
	$(eval TARGETS = $(patsubst $(SRC_DIR)%.cpp,$(DEST_DIR)%.o,$(SRCS)))
	@echo "New targets list $(TARGETS)"

# Build all object files
build: $(DEST_DIR)lexer.o $(DEST_DIR)parser.o $(TARGETS)


# Linker
link: $(TARGETS)
	$(CC) -o  $(PROJECT_NAME) $(addprefix $(DEST_DIR), $(notdir $(TARGETS))) -lfl


$(DEST_DIR)emitter.o: $(SRC_DIR)emitter.cpp $(SRC_DIR)global.h $(SRC_DIR)parser.hpp
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)lexer.o: $(SRC_DIR)lexer.cpp $(SRC_DIR)global.h $(SRC_DIR)parser.hpp
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)main.o: $(SRC_DIR)main.cpp $(SRC_DIR)global.h $(SRC_DIR)parser.hpp
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)parser.o: $(SRC_DIR)parser.cpp $(SRC_DIR)global.h $(SRC_DIR)parser.hpp 
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)tokens.o: $(SRC_DIR)tokens.cpp $(SRC_DIR)global.h $(SRC_DIR)parser.hpp $(SRC_DIR)tokens.h
	$(CC) -c $(CFLAGS) $< -o $@

$(DEST_DIR)symbol.o: $(SRC_DIR)symbol.cpp $(SRC_DIR)global.h $(SRC_DIR)symbol.h $(SRC_DIR)parser.hpp
	$(CC) -c $(CFLAGS) $< -o $@


# Clean up generated files and executable
clean:
	rm -f $(DEST_DIR)/*.o $(PROJECT_NAME)
	rm -f $(SRC_DIR)lexer.cpp
	rm -f $(SRC_DIR)parser.cpp
	rm -f $(SRC_DIR)parser.hpp
	rm -f $(SRC_DIR)parser.output

# Calling the default target on empty
.PHONY: all



