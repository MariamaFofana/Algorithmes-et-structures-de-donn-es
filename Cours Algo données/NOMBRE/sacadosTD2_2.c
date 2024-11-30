#include <stdio.h>
#define TRUE 1
#define FALSE 0
int main()
{
    int capacite;
    scanf("%d", &capacite);

    int poids;
    int tab[100]; // Tableau pour stocker les poids
    int nbObjets = 0;

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
    int possible[capacite + 1];
    possible[0] = TRUE; // La capacité 0 est atteignable (sac vide)

    for (int i = 1; i <= capacite; i++)
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
                int nouvelleCapacite = i + tab[j];
                if (nouvelleCapacite <= capacite)
                {
                    possible[nouvelleCapacite] = TRUE;
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
