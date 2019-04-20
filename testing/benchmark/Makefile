CC = gcc
FLAGS = -g
OBJ_FILES = $(wildcard ../../src/*.o)

SOURCES := $(wildcard *.c)

EXECUTABLES = $(SOURCES:.c=)

all: $(EXECUTABLES)

% : %.c 
		$(CC) $(FLAGS) $< -o $@ $(OBJ_FILES)

clean:
		rm -f $(EXECUTABLES)
