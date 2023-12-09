# Flags and Name
CC = gcc
CFLAGS = -Wall -Wextra -c
PROJECT_NAME = Notacja_wyrostkowa
#Flex
LEX_FILE = lexer.lex
FLEX_OUTPUT = lex.yy.c

# Directory where source files are located
SRC_DIR = comp
DEST_DIR = build
INCLUDES = $(wildcard $(SRC_DIR)/*.h)

# Get a list of all source files in the comp directory
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Create a list of target names (removing the .c extension)
TARGETS = $(patsubst $(SRC_DIR)/%.c,$(DEST_DIR)/%.o,$(SRCS))
# Default target
all : makedir build 
flex : makedir $(SRC_DIR)/lexer.c build 
# Generating lex
$(SRC_DIR)/lexer.c: $(LEX_FILE)
	flex $(LEX_FILE)
	move $(SRC_DIR)\lexer.c old-lexer.c
	move $(FLEX_OUTPUT) $(SRC_DIR)\lexer.c

# build all object files
build: $(TARGETS) 
	$(CC) -o $(PROJECT_NAME) $(addprefix $(DEST_DIR)/, $(notdir $(TARGETS)))


$(DEST_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -o $@ $<

	
# make build dir if doesnt exists already
makedir:
	if not exist $(DEST_DIR) mkdir $(DEST_DIR)

# Clean up generated files and exe
clean:
	del /q /s "$(DEST_DIR)\*.o"
	del $(PROJECT_NAME).exe
	move old-lexer.c $(SRC_DIR)\lexer.c

# Calling default target on empty
.PHONY: all
