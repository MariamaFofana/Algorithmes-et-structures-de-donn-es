#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* les trois valeurs de status */
#define EMPTY 0
#define SET 1
#define REMOVED 2

typedef struct {
  char *key;
  int status;
  char *val;
} Data;

typedef struct {
  Data *tab;
  int size;
} HashTable;

/* le status peut-être affiché de cette manière à des fins de débugage :
 * printf("%s\n",Labels[h->tab[i].status]);
 */
const char *Labels[] = {"Empty", "Set", "Removed"};

void error(void);

HashTable *Init(int size);
int Query(HashTable *h, char *key, int *indice);
void Insert(HashTable *h, char *key, char *val);
void Delete(HashTable *h, char *key);
void Stats(HashTable *h);
void Print(HashTable *h);
void Destroy(HashTable *h);

int main(void) {
  int size;
  char lecture[100];
  char *key;
  char *val;
  HashTable *h;

  if (fscanf(stdin, "%99s", lecture) != 1)
    error();
  while (strcmp(lecture, "bye") != 0) {
    if (strcmp(lecture, "init") == 0) {
      if (fscanf(stdin, "%99s", lecture) != 1)
        error();
      size = atoi(lecture);
      h = Init(size);
    } else if (strcmp(lecture, "insert") == 0) {
      if (fscanf(stdin, "%99s", lecture) != 1)
        error();
      key = strdup(lecture);
      if (fscanf(stdin, "%99s", lecture) != 1)
        error();
      val = strdup(lecture);
      Insert(h, key, val);
    } else if (strcmp(lecture, "delete") == 0) {
      if (fscanf(stdin, "%99s", lecture) != 1)
        error();
      key = strdup(lecture);
      Delete(h, lecture);
    } else if (strcmp(lecture, "query") == 0) {
      if (fscanf(stdin, "%99s", lecture) != 1)
        error();
      int i;
      if (Query(h, lecture, &i) >= 0) {
        printf("%s\r\n", h->tab[i].val);
      } else {
        printf("Not found\r\n");
      }
    } else if (strcmp(lecture, "destroy") == 0) {
      Destroy(h);
    } else if (strcmp(lecture, "stats") == 0) {
      Stats(h);
    } else if (strcmp(lecture, "print") == 0) {
      Print(h);
    }

    if (fscanf(stdin, "%99s", lecture) != 1)
      error();
  }
  return 0;
}

/* fonction de décalage de bit circulaire */
unsigned int shift_rotate(unsigned int val, unsigned int n) {
  n = n % (sizeof(unsigned int) * 8);
  return (val << n) | (val >> (sizeof(unsigned int) * 8 - n));
}

/* fonction d'encodage d'une chaîne de caractères */
unsigned int Encode(char *key) {
  unsigned int i;
  unsigned int val = 0;
  unsigned int power = 0;
  for (i = 0; i < strlen(key); i++) {
    val += shift_rotate(key[i], power * 7);
    power++;
  }
  return val;
}

/* fonction de hachage simple qui prend le modulo */
unsigned int hash(unsigned int val, unsigned int size) { return val % size; }

/* fonction de hachage complète à utiliser */
unsigned int HashFunction(char *key, unsigned int size) {
  return hash(Encode(key), size);
}

void error(void) {
  printf("input error\r\n");
  exit(0);
}

HashTable *Init(int size) {
  HashTable *h;
  h = malloc(sizeof(HashTable));
  h->tab = malloc(sizeof(Data) * size);
  h->size = size;
  int i;
  for (i = 0; i < size; i++) {
    h->tab[i].status = EMPTY;
  }
  return h;
}

int Query(HashTable *h, char *key, int *indice) {

  const unsigned int first_index = HashFunction(key, h->size);
  unsigned int index = (unsigned int)first_index;

  Data current_cell = h->tab[index];
  while (current_cell.status != SET || strcmp(current_cell.key, key) != 0) {
    index = (index + 1) % h->size;
    current_cell = h->tab[index];

    // si on a parcouru tout le tableau (pas trouvé)
    if (index == first_index)
      return -1;
  }
  *indice = (int)index;

  // si on est jamais rentré dans la boucle
  if (index == first_index)
    return 1;

  return 0;
}

void Insert(HashTable *h, char *key, char *val) {
  Data data = {.key = key, .status = SET, .val = val};

  const unsigned int first_index = HashFunction(key, h->size);
  unsigned int index = (unsigned int)first_index;

  Data current_cell = h->tab[index];
  while (current_cell.status == SET && strcmp(key, current_cell.key) != 0) {
    index = (index + 1) % h->size;
    current_cell = h->tab[index];

    // si on a parcouru tout le tableau (tableau plein)
    if (index == first_index) {
      return;
    }
  }

  h->tab[index] = data;
}

void Delete(HashTable *h, char *key) {
  Data data = {.status = REMOVED};

  int index;
  if (Query(h, key, &index) < 0)
    printf("Not found\r\n");

  h->tab[index] = data;
}

void mkstats(HashTable *h, int *empty, int *deleted, int *used) {
  *empty = *used = *deleted = 0;
  int i;
  for (i = 0; i < h->size; i++) {
    switch (h->tab[i].status) {
    case EMPTY:
      *empty += 1;
      break;
    case SET:
      *used += 1;
      break;
    case REMOVED:
      *deleted += 1;
      break;
    default:
      break;
    }
  }
}
void Stats(HashTable *h) {
  int empty, deleted, used;
  mkstats(h, &empty, &deleted, &used);

  printf("%-8s: %d\r\n", "size", h->size);
  printf("%-8s: %d\r\n", "empty", empty);
  printf("%-8s: %d\r\n", "deleted", deleted);
  printf("%-8s: %d\r\n", "used", used);
}

void Destroy(HashTable *h) {
  free(h->tab);
  free(h);
}

void Print(HashTable *h) {
  int i;
  for (i = 0; i < h->size; i++) {
    printf("%d - ", i);
    printf("%s ", Labels[h->tab[i].status]);
    if (h->tab[i].status == SET) {
      printf("- %s ", h->tab[i].key);
      printf("- %s ", h->tab[i].val);
    }
    printf("\n");
  }
}