CC = gcc
FLAGS = -g

SOURCES := $(wildcard *.c)

EXECUTABLES = $(SOURCES:.c=)

all: $(EXECUTABLES)

% : %.c smart_string.h
		$(CC) $(FLAGS)  $< -o $@

clean:
		rm -f $(EXECUTABLES)
