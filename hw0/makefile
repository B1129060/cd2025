CC = gcc
OBJS = main.o

all: test

%.o: %.c
  $(CC) -c -o $@ $<

test: $(OBJS)
  $(CC) -o $@ $^
