# Compiler options
CC=gcc
CFLAGS=-c -Wall -std=gnu99
LDFLAGS=-lm

# File options
SRCDIR=src
SOURCES=$(addprefix $(SRCDIR)/, main.c land.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=animals

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
