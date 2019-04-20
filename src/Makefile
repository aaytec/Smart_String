CC = gcc
FLAGS = -g -c

SOURCES := $(wildcard *.c)

OBJ_FILES = $(SOURCES:.c=)
OBJ_FILES_ = $(wildcard *.o)

all: $(OBJ_FILES)

% : %.c *.h
		$(CC) $(FLAGS) $< 

clean:
		rm -f $(OBJ_FILES_)
