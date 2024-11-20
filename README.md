# Sudoku Résolution avec Threads en C

Ce projet implémente une résolution parallèle d'un puzzle de Sudoku en utilisant des threads. Il utilise la technique de retour en arrière (backtracking) pour résoudre la grille et les threads pour vérifier plusieurs solutions simultanément.

## Description

Le programme génère une grille de Sudoku valide et la résout en utilisant la méthode de **backtracking**. Pour rendre la résolution plus rapide, le programme utilise des **threads** qui tentent de résoudre simultanément différentes valeurs dans les cases vides de la grille. Le processus est parallèle et assure une résolution rapide du puzzle.

### Fonctionnalités principales

- **Génération de la grille de Sudoku** : Le programme génère une solution valide de Sudoku.
- **Réduction de la grille** : Après avoir généré une solution, le programme réduit la grille en supprimant des valeurs tout en garantissant que la grille reste résoluble.
- **Utilisation des Threads** : Le programme crée plusieurs threads qui tentent de résoudre la grille en parallèle, chacun essayant un numéro différent dans une case vide donnée.
- **Synchronisation avec Mutex et Condition Variables** : Les threads utilisent un mutex pour protéger l'accès aux ressources partagées (grille de Sudoku) et une variable de condition pour gérer la synchronisation entre threads.


