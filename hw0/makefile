CC = gcc
OBJS = main.o

all: hw0

%.o: %.c
	$(CC) -c -o $@ $<

hw0: $(OBJS)
	$(CC) -o $@ $^

.PHONY: clean
clean:
	rm hw0 *.o

