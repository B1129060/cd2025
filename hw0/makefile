CC = gcc
OBJS = a.o b.o c.o

all: test

%.o: %.c
  $(CC) -c -o $@ $<

test: $(OBJS)
  $(CC) -o $@ $^
