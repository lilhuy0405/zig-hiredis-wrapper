CC=gcc
CFLAGS=-I.
LIBS=-lhiredis

all: redis_example

redis_example: main.c redis_lib.c
	$(CC) -o redis_example main.c redis_lib.c $(CFLAGS) $(LIBS)

clean:
	rm -f redis_example