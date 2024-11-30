#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int allocated; /* allocation actuelle du tableau */
  int filled;    /* nombre d'éléments présents dans le tas binaire */
  int *array;    /* tableau des valeurs */
} BinaryHeap;

/* Init alloue la structure BinaryHeap et également le membre array avec la taille donnée
 * elle remplit également allocated (taille) et initialise filled à 0 */
BinaryHeap * Init(int size);

/* InsertValue insère une valeur dans le tas binaire le tableau est réalloué si nécessaire 
(allocated changé par rapport à la nouvelle taille) * filled est incrémenté de 1 */
void InsertValue(BinaryHeap * heap, int value);

/* ExtractMax retourne 0 si le tas binaire est vide sinon, elle retourne 1 et remplit val avec la valeur maximale
 * présente dans le tas binaire filled est décrémenté de 1 et la valeur max est supprimée du tas binaire */
int ExtractMax(BinaryHeap * heap, int * val);

/* Destroy libère la structure et le tableau */
void Destroy(BinaryHeap * heap);


int main(void) 
{
  char lecture[100];
  int val;
  BinaryHeap * heap;
  heap = Init(10);

  fscanf(stdin,"%99s",lecture);
  while (strcmp(lecture,"bye")!=0) {
    if (strcmp(lecture,"insert")==0) {
      fscanf(stdin,"%99s",lecture);
      val = strtol(lecture,NULL,10);
      InsertValue(heap,val);
    } else if (strcmp(lecture,"extract")==0) {
      if(ExtractMax(heap,&val))
      {
        printf("%d\r\n",val);
      }
    }
    fscanf(stdin,"%99s",lecture);
  }
  Destroy(heap);
  return 0;
}
//  Elle crée un tas vide avec une capacité initiale (allocated) de size éléments, et filled est initialisé à 0. 
BinaryHeap * Init(int size)
{
  BinaryHeap * heap;
  heap = malloc(sizeof(BinaryHeap));
  heap->allocated = size;
  heap->filled = 0;
  heap->array = malloc(sizeof(int)*size);
  return heap;
}

void InsertValue(BinaryHeap * heap, int value) {
  // Vérifier si le tableau est plein et doubler la taille si nécessaire
  if (heap->filled == heap->allocated) {
    // Allouer un nouveau tableau avec le double de la taille actuelle
    int *newtab = (int*)malloc(2 * heap->allocated * sizeof(int));
    if (!newtab) {
      printf("Erreur d'allocation de mémoire\n");
      return;
    }
    // Copier les éléments de l'ancien tableau vers le nouveau
    for (int j = 0; j < heap->filled; j++) {
      newtab[j] = heap->array[j];
    }
    // Libérer l'ancien tableau et mettre à jour le pointeur et la taille
    free(heap->array);
    heap->array = newtab;
    heap->allocated *= 2;
  }

  // Ajouter la valeur à la fin du tableau
  heap->array[heap->filled] = value;
  int i = heap->filled;
  heap->filled++;

  // Remonter la valeur pour maintenir la propriété max-heap
  while (i > 0 && heap->array[(i - 1) / 2] < heap->array[i]) {
    // Échange avec le parent
    int temp = heap->array[i];
    heap->array[i] = heap->array[(i - 1) / 2];
    heap->array[(i - 1) / 2] = temp;
    
    // Mettre à jour l'indice pour remonter au parent
    i = (i - 1) / 2;
  }
}

int ExtractMax(BinaryHeap * heap, int *res) {
  if (heap->filled == 0) {
    return 0; // Échec, tas vide
  }

  // Récupère la valeur maximale (racine du tas)
  *res = heap->array[0];

  // Remplace la racine par le dernier élément
  heap->array[0] = heap->array[heap->filled - 1];
  heap->filled--;

  // Descend pour maintenir la propriété de tas max
  int i = 0;
  while (1) {
    int left = 2 * i + 1; // Indice de l'enfant gauche
    int right = 2 * i + 2; // Indice de l'enfant droit
    int largest = i;

    // Vérifie si l'enfant gauche existe et est plus grand
    if (left < heap->filled && heap->array[left] > heap->array[largest]) {
      largest = left;
    }

    // Vérifie si l'enfant droit existe et est plus grand
    if (right < heap->filled && heap->array[right] > heap->array[largest]) {
      largest = right;
    }

    // Si l'élément actuel est plus grand que ses enfants, la propriété est respectée
    if (largest == i) {
      break;
    }

    // Échange avec le plus grand des enfants
    int temp = heap->array[i];
    heap->array[i] = heap->array[largest];
    heap->array[largest] = temp;

    // Mettre à jour l'indice pour descendre au niveau suivant
    i = largest;
  }

  return 1; // Extraction réussie
}


void Destroy(BinaryHeap * heap)
{
	if (heap) {
		free(heap->array);
		free(heap);
	}
}
