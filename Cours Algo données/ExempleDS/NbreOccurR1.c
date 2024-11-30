#include <stdio.h>
#define MAX_VAL 100
#define MIN_VAL -100

int main() {
    int nbretotal; 
    scanf("%d", &nbretotal); // Lire le nombre total d'éléments
    int tab[nbretotal];

    // Lecture des éléments
    for (int i = 0; i < nbretotal; i++) {
        scanf("%d", &tab[i]);
    }

    // Initialisation du tableau de comptage
    int valpossible = MAX_VAL - MIN_VAL + 1;
    int tabocc[valpossible];
    for (int j = 0; j < valpossible; j++) {
        tabocc[j] = 0; // Initialisation à 0
    }

    // Comptage des occurrences
    for (int i = 0; i < nbretotal; i++) {
        int index = tab[i] - MIN_VAL; // Calcul de l'index dans tabocc
        if (index >= 0 && index < valpossible) {
            tabocc[index]++;
        }
    }

    // Trouver le nombre avec le plus d'occurrences
    int max_count = 0;
    int result = MIN_VAL;

    for (int i = 0; i < valpossible; i++) {
        if (tabocc[i] > max_count || 
           (tabocc[i] == max_count && (i + MIN_VAL) > result)) {
            max_count = tabocc[i];
            result = i + MIN_VAL; // Récupérer la valeur réelle
        }
    }

    // Affichage du résultat
    printf("%d\r\n", result);

    return 0;
}
