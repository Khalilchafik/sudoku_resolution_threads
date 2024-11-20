#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

int **sudoku_init();
void sudoku_free(int **sudoku);
void sudoku_print(int **sudoku);
int sudoku_get(int **sudoku, int x, int y);
void sudoku_set(int **sudoku, int x, int y, int value);

#endif /* SUDOKU_H */
