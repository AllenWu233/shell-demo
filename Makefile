CC = gcc
CFLAGS = -Wall 

SRCDIR = src
BINDIR = .
OBJDIR = $(SRCDIR)

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGET = main

$(BINDIR)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

debug: CFLAGS += -g -DDEBUG
debug: $(BINDIR)/$(TARGET)

.PHONY: clean

clean:
	rm -f $(OBJ) $(BINDIR)/$(TARGET)


