// auteur du projet : CHAFIK Khalil
#include "sudoku.h"

// Fonction pour initialiser une grille de Sudoku
int **sudoku_init() {
    // Alloue de la mémoire pour les lignes de la grille
    int **grille = malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++) {
        // Alloue de la mémoire pour chaque ligne
        grille[i] = malloc(SIZE * sizeof(int));
        for (int j = 0; j < SIZE; j++) {
            // Initialise chaque case de la grille à 0
            grille[i][j] = 0;
        }
    }
    return grille; // Retourne la grille initialisée
}

// Fonction pour libérer la mémoire allouée pour une grille de Sudoku
void sudoku_free(int **sudoku) {
    for (int i = 0; i < SIZE; i++) {
        free(sudoku[i]); // Libère la mémoire de chaque ligne
    }
    free(sudoku); // Libère la mémoire du tableau de pointeurs
}

// Fonction pour afficher une grille de Sudoku
void sudoku_print(int **sudoku) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Affiche chaque valeur de la grille, suivie d'un espace
            printf("%d ", sudoku[i][j]);
        }
        // Passe à la ligne suivante après avoir affiché une ligne entière
        printf("\n");
    }
}

// Fonction pour récupérer la valeur d'une case dans la grille
int sudoku_get(int **sudoku, int x, int y) {
    return sudoku[x][y]; // Retourne la valeur à la position (x, y)
}

// Fonction pour modifier la valeur d'une case dans la grille
void sudoku_set(int **sudoku, int x, int y, int value) {
    sudoku[x][y] = value; // Modifie la valeur à la position (x, y)
}
