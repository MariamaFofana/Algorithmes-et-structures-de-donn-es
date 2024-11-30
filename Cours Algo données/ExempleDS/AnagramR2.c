#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

int main() {
    char chaine1[100], chaine2[100]; 
    scanf("%s", chaine1);
    scanf("%s", chaine2);
    
    if (strlen(chaine1) != strlen(chaine2)) {
        printf("n\r\n");
        return 0;
    }
    
   if (strcmp(chaine1, chaine2) == 0) {
        printf("n\r\n");
        return 0;
    }
    // Tableau de fréquence pour les lettres
    int freq[ALPHABET_SIZE] = {0};

    // Calculer les fréquences pour chaine1 (incrémentation)
    for (int i = 0; chaine1[i] != '\0'; i++) {
        freq[chaine1[i] - 'a']++;
    }

    // Calculer les fréquences pour chaine2 (décrémentation)
    for (int i = 0; chaine2[i] != '\0'; i++) {
        freq[chaine2[i] - 'a']--;
    }

    // Vérifier si toutes les fréquences sont nulles
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq[i] != 0) {
            printf("n\r\n");
            return 0;
        }
    }

    // Si toutes les fréquences sont nulles, les mots sont des anagrammes
    printf("o\r\n");
    return 0;
}
