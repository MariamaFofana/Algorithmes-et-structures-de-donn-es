#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAILLE_MAX 100

typedef struct {
    int debut;           
    int fin;             
    int taille;          
    int tableau[TAILLE_MAX]; 
} laFile;

void initialiserFile(laFile *file) {
    file->debut = 0;
    file->fin = 0;
    file->taille = 0;
}
int pleine(laFile *file) {
    return file->taille == TAILLE_MAX - 1;
}
// vide renvoie un bool vrai si la file est vide 
bool vide(laFile *file) {
    return file->taille == 0;
}
// place la valeur v dans la file  Quand l’indice devient supérieur à la taille du tableau, on le met à zéro
void Enfiler(laFile *file, int v) {
    if (!pleine(file)) {              
        file->tableau[file->fin] = v;             
        file->fin = (file->fin + 1) % TAILLE_MAX; 
        file->taille++;                           
    } 
}
// renvoie la prochaine valeur et la retire 
int Defiler(laFile *file) {
    if (!vide(file)) {                            
        int valeur = file->tableau[file->debut];  
        file->debut = (file->debut + 1) % TAILLE_MAX; 
        file->taille--;  
        printf("%d\r\n", valeur);                          
        return valeur;
    } 
}

int main() {
    char commande[10];
    int valeur;
    laFile file;
    initialiserFile(&file);

    while (1) {
        scanf("%s", commande);  

        if (strcmp(commande, "queue") == 0) {
            scanf("%d", &valeur);
            Enfiler(&file, valeur);
        } else if (strcmp(commande, "dequeue") == 0) {
            Defiler(&file);
        } else if (strcmp(commande, "bye") == 0) {
            break;
        }
    }

    return 0;
}
