CC=gcc
LDFLAGS=-lm

binaries:sort

all: $(binaries)

sort: sorting.c board.c bstr.c
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	$(RM) -f $(binaries) *.o
	