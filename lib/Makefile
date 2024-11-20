CC=gcc
CFLAGS=-Wall -g
SRC=sudoku.c
OBJ=$(SRC:.c=.o)

all: libsudoku.a

libsudoku.a: $(OBJ)
	ar rcs libsudoku.a $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o *.a

.PHONY: all clean
