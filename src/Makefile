CC=gcc
CFLAGS=-I../lib -Wall -pthread -g
LDFLAGS=-L../lib -lsudoku
SRC=main.c
OBJ=$(SRC:.c=.o)
EXEC=../bin/sudoku

all: $(EXEC)

$(EXEC): $(OBJ) ../lib/libsudoku.a
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o $(EXEC)

.PHONY: all clean
