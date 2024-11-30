#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
   
    double tab[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf", &tab[i]);
    }
    
    int maxLength = 1; // Longueur maximale de sous-séquence
    int currentLength = 1; // Longueur de la sous-séquence actuelle
    
    // Parcourir la séquence
    for (int i = 1; i < n; i++) {
        if (tab[i] == tab[i - 1]) {
            // Si le nombre courant est égal au précédent
            currentLength++;
        } else {
            // Si on rencontre un nombre différent
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
            currentLength = 1; // Réinitialiser la longueur de la sous-séquence
        }
    }
    
    // Comparer la dernière sous-séquence
    if (currentLength > maxLength) {
        maxLength = currentLength;
    }
    
    // Afficher la longueur maximale de la sous-séquence
    printf("%d\n", maxLength);
    
    return 0;
}
