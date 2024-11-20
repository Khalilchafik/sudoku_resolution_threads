// auteur du projet : CHAFIK Khalil
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include "sudoku.h"

// Définitions des constantes
#define TAILLE 9  // Taille de la grille de Sudoku
#define NOMBRE_THREADS 8  // Nombre de threads à utiliser

// Structure pour passer les arguments aux threads
typedef struct {
    int **grille;  // Pointeur vers la grille de Sudoku
    int ligne;  // Ligne à traiter
    int colonne;  // Colonne à traiter
    int numero;  // Numéro à essayer dans la case
    bool *solutionTrouvee;  // Indicateur si une solution a été trouvée
    pthread_mutex_t *mutex;  // Mutex pour protéger l'accès partagé
    pthread_cond_t *cond;  // Condition variable pour la synchronisation des threads
} ArgumentsThread;

// Déclarations des fonctions
bool resoudreSudoku(int **grille);
void genererSolution(int **grille);
int** sudoku_init();
void sudoku_free(int **grille);
void sudoku_print(int **grille);
void copierGrille(int **dest, int **src);

// Initialisation de la grille de Sudoku
int** sudoku_init() {
    // Allocation de mémoire pour la grille
    int **grille = malloc(TAILLE * sizeof(int*));
    if (grille == NULL) {
        // Vérification de l'allocation de mémoire
        fprintf(stderr, "Échec de l'allocation de mémoire\n");
        exit(1);
    }
    // Allocation de mémoire pour chaque ligne de la grille
    for (int i = 0; i < TAILLE; i++) {
        grille[i] = malloc(TAILLE * sizeof(int));
        if (grille[i] == NULL) {
            fprintf(stderr, "Échec de l'allocation de mémoire\n");
            exit(1);
        }
        // Initialisation des cases de la grille à 0
        for (int j = 0; j < TAILLE; j++) {
            grille[i][j] = 0;
        }
    }
    return grille;  // Retourne la grille initialisée
}

// Libération de la mémoire allouée pour la grille de Sudoku
void sudoku_free(int **grille) {
    for (int i = 0; i < TAILLE; i++) {
        free(grille[i]);  // Libère chaque ligne
    }
    free(grille);  // Libère le tableau de pointeurs
}

// Affichage de la grille de Sudoku
void sudoku_print(int **grille) {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            printf("%d ", grille[i][j]);  // Affiche chaque valeur suivie d'un espace
        }
        printf("\n");  // Nouvelle ligne après chaque ligne de la grille
    }
}

// Vérifier s'il est sûr de placer un numéro à une position dans la grille
bool estSecurise(int **grille, int ligne, int colonne, int numero) {
    for (int d = 0; d < TAILLE; ++d) {  // Vérifie la ligne
        if (grille[ligne][d] == numero) {
            return false;  // Numéro déjà présent dans la ligne
        }
    }
    for (int r = 0; r < TAILLE; ++r) {  // Vérifie la colonne
        if (grille[r][colonne] == numero) {
            return false;  // Numéro déjà présent dans la colonne
        }
    }
    // Vérifie le bloc 3x3
    int debutLigne = ligne - ligne % 3;
    int debutColonne = colonne - colonne % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grille[i + debutLigne][j + debutColonne] == numero) {
                return false;  // Numéro déjà présent dans le bloc 3x3
            }
        }
    }
    return true;  // Numéro peut être placé en toute sécurité
}

// Résoudre le Sudoku en utilisant la méthode de retour en arrière
bool resoudreSudoku(int **grille) {
    int ligne = -1;
    int colonne = -1;
    bool estVide = true;
    // Trouve une case vide dans la grille
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (grille[i][j] == 0) {
                ligne = i;
                colonne = j;
                estVide = false;
                break;  // Sort de la boucle dès qu'une case vide est trouvée
            }
        }
        if (!estVide) {
            break;
        }
    }
    if (estVide) {
        return true;  // Pas de case vide, grille résolue
    }
    // Essaye les numéros de 1 à 9
    for (int numero = 1; numero <= TAILLE; numero++) {
        if (estSecurise(grille, ligne, colonne, numero)) {
            grille[ligne][colonne] = numero;
            if (resoudreSudoku(grille)) {
                return true;  // Si la grille peut être résolue avec ce numéro, retourne vrai
            }
            grille[ligne][colonne] = 0;  // Revenir en arrière si la solution échoue
        }
    }
    return false;  // Retourne faux si aucune solution n'est trouvée
}

// Générer une grille de Sudoku résoluble
void genererSolution(int **grille) {
    // Initialise la grille avec des zéros
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            grille[i][j] = 0;
        }
    }
    // Remplit la grille avec une solution valide
    resoudreSudoku(grille);
}

// Fonction pour copier une grille
void copierGrille(int **dest, int **src) {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            dest[i][j] = src[i][j];  // Copie chaque élément de la grille source vers la grille destination
        }
    }
}

// Fonction exécutée par chaque thread
void *thread_resolveur(void *arg) {
    ArgumentsThread *data = (ArgumentsThread *)arg;

    // Initialise une grille temporaire
    int **tempGrille = sudoku_init();
    if (tempGrille == NULL) {
        fprintf(stderr, "Échec de l'allocation de mémoire\n");
        pthread_exit(NULL);
    }

    // Copie la grille courante dans la grille temporaire
    copierGrille(tempGrille, data->grille);
    // Place le numéro proposé dans la grille temporaire
    tempGrille[data->ligne][data->colonne] = data->numero;
    
    // Résoudre la grille temporaire
    if (resoudreSudoku(tempGrille)) {
        // Si la solution est trouvée, mettre à jour le flag solutionTrouvee
        pthread_mutex_lock(data->mutex);
        *data->solutionTrouvee = true;
        // Notifier tous les threads pour arrêter
        pthread_cond_broadcast(data->cond);
        pthread_mutex_unlock(data->mutex);
    }
    
    // Libère la grille temporaire
    sudoku_free(tempGrille);
    pthread_exit(NULL);
}

// Réduire la grille pour n'avoir que N indices tout en garantissant qu'elle reste résoluble
void reduireGrille(int **grille, int N) {
    int remplis = TAILLE * TAILLE;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_t cond;
    pthread_cond_init(&cond, NULL);
    
    // Réduire la grille jusqu'à ce qu'il ne reste que N cases remplies
    while (remplis > N) {
        int ligne = rand() % TAILLE;
        int colonne = rand() % TAILLE;
        if (grille[ligne][colonne] != 0) {
            int original = grille[ligne][colonne];
            grille[ligne][colonne] = 0;
            
            bool solutionTrouvee = false;
            pthread_t threads[NOMBRE_THREADS];
            ArgumentsThread args[NOMBRE_THREADS];
            
            // Crée des threads pour vérifier les solutions possibles
            for (int i = 0, numero = 1; i < NOMBRE_THREADS; numero++) {
                if (numero == original) continue;

                args[i] = (ArgumentsThread){grille, ligne, colonne, numero, &solutionTrouvee, &mutex, &cond};
                if (pthread_create(&threads[i], NULL, thread_resolveur, &args[i]) != 0) {
                    perror("Échec de la création du thread");
                    exit(1);
                }
                i++;
            }

            pthread_mutex_lock(&mutex);
            while (!solutionTrouvee) {
                pthread_cond_wait(&cond, &mutex);
            }
            pthread_mutex_unlock(&mutex);

            // Annule et joint tous les threads
            for (int k = 0; k < NOMBRE_THREADS; k++) {
                pthread_cancel(threads[k]);
                pthread_join(threads[k], NULL);
            }

            if (!solutionTrouvee) {
                // Si aucune solution n'a été trouvée, remet la valeur originale
                grille[ligne][colonne] = original;
            } else {
                remplis--;  // Décrémente le compteur des cases remplies
            }
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

// Fonction principale
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N < 1 || N > 81) {
        printf("N doit être compris entre 1 et 81.\n");
        return 1;
    }

    srand(time(NULL));  // Initialise le générateur de nombres aléatoires
    int **grille = sudoku_init();
    genererSolution(grille);
    reduireGrille(grille, N);
    sudoku_print(grille);
    sudoku_free(grille);
    return 0;
}
