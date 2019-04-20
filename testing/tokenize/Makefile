CC = gcc
FLAGS = -g
OBJ_FILES = $(wildcard ../../src/*.o)

SOURCES := $(wildcard *.c)

EXECUTABLES = $(SOURCES:.c=)

all: $(EXECUTABLES)

% : %.c 
		$(CC) $(FLAGS) $(OBJ_FILES) $< -o $@ 

clean:
		rm -f $(EXECUTABLES)
