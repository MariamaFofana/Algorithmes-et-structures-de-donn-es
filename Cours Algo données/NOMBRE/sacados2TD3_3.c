#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define UTILISER 1
#define NONUTILISER 0
int main()
{
    // Lire la capacité du sac.
    int capacite;
    scanf("%d", &capacite);

    int poids;
    int tab[100]; // Tableau pour stocker les poids
    int nbObjets = 0;
    // Lire les objets jusqu'à rencontrer -1.
    while (TRUE)
    {
        scanf("%d", &poids);
        if (poids == -1)
        {
            break;
        }
        tab[nbObjets] = poids;
        nbObjets++;
    }
    // tableau de capacite et elem
    int possible[capacite + 1];
    possible[0] = TRUE; // La capacité 0 est atteignable (sac vide)

    for (int i = 1; i <= capacite; i++)
    {
        {
            possible[i] = FALSE;
        }
        // ajouter delem
        for (int i = 0; i <= capacite; i++)
        {
            if (possible[i] == TRUE)
            {
                for (int j = 0; j < nbObjets; j++)
                {
                    for (int i = capacite; i >= tab[j]; i--)
                    { 
                        if (possible[i - tab[j]] == TRUE)
                        {                   
                            possible[i] = TRUE; 
                        }
                    }
                }
            }
        }

        if (possible[capacite] == TRUE)
        {
            printf("OUI\r\n");
        }
        else
        {
            printf("NON\r\n");
        }

        return 0;
    }
}