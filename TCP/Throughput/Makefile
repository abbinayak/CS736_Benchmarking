.PHONY: client_thr server_thr clean all local

CC=gcc
CFLAGS=-I. -O3 -Wall -pedantic -g
DEPS = connection.h
PORT=12345

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: client_thr server_thr

client_thr: client_thr.o
	$(CC) -o $@ $^ $(CFLAGS)

server_thr: server_thr.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o client_thr server_thr

local: client_thr server_thr
	./server_thr $(PORT) &
	./client_thr localhost $(PORT)

