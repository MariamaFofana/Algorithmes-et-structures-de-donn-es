#include <stdio.h>

#define MAX 100 

int main() {
    int N;
    int grid[MAX][MAX]; 
    int dp[MAX][MAX];  

    // Étape 1 : Lecture de la taille et de la grille
    printf("Entrez la taille de la grille N : ");
    scanf("%d", &N);

    printf("Entrez les cases de la grille (1 pour libre, 0 pour obstacle) :\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Étape 2 : Initialisation de la matrice DP
    if (grid[0][0] == 0) {
        dp[0][0] = 0; 
    } else {
        dp[0][0] = 1; 
    }

    // Initialise la première colonne
    for (int i = 1; i < N; i++) {
        if (grid[i][0] == 0) {
            dp[i][0] = 0; // Pas de chemin si case bloquée
        } else {
            dp[i][0] = dp[i-1][0]; // Chemin venant du haut
        }
    }

    // Initialise la première ligne
    for (int j = 1; j < N; j++) {
        if (grid[0][j] == 0) {
            dp[0][j] = 0; // Pas de chemin si case bloquée
        } else {
            dp[0][j] = dp[0][j-1]; // Chemin venant de la gauche
        }
    }

    // Étape 3 : Remplissage de la matrice DP
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (grid[i][j] == 0) {
                dp[i][j] = 0; // Pas de chemin si case bloquée
            } else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1]; // Somme des chemins
            }
        }
    }

    // Étape 4 : Résultat final
    printf("Nombre de chemins distincts possibles : %d\n", dp[N-1][N-1]);

    return 0;
}
