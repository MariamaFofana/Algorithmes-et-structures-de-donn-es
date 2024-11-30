#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* les trois valeurs de status */
#define EMPTY 0
#define SET 1
#define REMOVED 2
// une cellule de la table 
typedef struct {
   char * key; 
   int status;
   char * val;
} Data;
// la table de hachage
typedef struct {
  Data * tab;
  int size;
} HashTable;

/* le status peut-être affiché de cette manière à des fins de débugage :
 * printf("%s\n",Labels[h->tab[i].status]);
 */
const char * Labels[] = {"Empty","Set","Removed"};

void error(void);

HashTable * Init(int size);
int Query(HashTable * h, char * key, int * indice);
void Insert(HashTable * h, char * key, char * val);
void Delete(HashTable * h, char * key);
void Stats(HashTable * h);
void Print(HashTable * h);
void Destroy(HashTable * h);

int main(void) 
{
   int size;
   char lecture[100];
   char * key;
   char * val;
   HashTable * h;

   if (fscanf(stdin,"%99s",lecture)!=1)
      error();
   while (strcmp(lecture,"bye")!=0)
   {
      if (strcmp(lecture,"init")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         size = atoi(lecture);
         h = Init(size);
      }
      else if (strcmp(lecture,"insert")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         key = strdup(lecture);
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         val = strdup(lecture);
         Insert(h,key,val);
      }
      else if (strcmp(lecture,"delete")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         key = strdup(lecture);
         Delete(h,lecture);
      }
      else if (strcmp(lecture,"query")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         int i;
         if (Query(h,lecture,&i)) {
            printf("%s\r\n",h->tab[i].val);
         }
         else {
            printf("Not found\r\n");
         }
      }
      else if (strcmp(lecture,"destroy")==0)
      {
         Destroy(h);
      }
      else if (strcmp(lecture,"stats")==0)
      {
         Stats(h);
      }
      else if (strcmp(lecture,"print")==0)
      {
         Print(h);
      }

      if (fscanf(stdin,"%99s",lecture)!=1)
         error();
   }
   return 0;
}

/* fonction de décalage de bit circulaire */
unsigned int shift_rotate(unsigned int val, unsigned int n)
{
  n = n%(sizeof(unsigned int)*8);
  return (val<<n) | (val>> (sizeof(unsigned int)*8-n));
}

/* fonction d'encodage d'une chaîne de caractères */
unsigned int Encode(char * key)
{
   unsigned int i;
   unsigned int val = 0;
   unsigned int power = 0;
   for (i=0;i<strlen(key);i++)
   {
     val += shift_rotate(key[i],power*7);
     power++;
   }
   return val;
}

/* fonction de hachage simple qui prend le modulo */
unsigned int hash(unsigned int val, unsigned int size)
{
   return val%size;
}

/* fonction de hachage complète à utiliser */
unsigned int HashFunction(char * key, unsigned int size)
{
   return hash(Encode(key),size);
}

void error(void)
{
   printf("input error\r\n");
   exit(0);
}

HashTable * Init(int size) {
   HashTable * h;
   h = (HashTable*)(sizeof(HashTable));
   h->tab = (Data *) malloc(sizeof(Data)*size);
   h->size = size;
   int i;
   for (i=0;i<size;i++) {
      h->tab[i].status = EMPTY;
   }
   return h;
}
//La commande query permet de faire une requête sur une clé on utilise la fonction HashFunction et init 
// renvoie  1 si trouvé indice reprensete lendroit 0 si pas trouvé avec removed  memoriser son etat  -1table pleine 
int Query(HashTable * h, char * key, int * indice) {

   unsigned int hashkey = HashFunction(key, h->size);
   unsigned int i = 0;
   unsigned int iremoved = -1;
   while (h->tab[hashkey].status != EMPTY && i < h->size)
   {
    if(h->tab[hashkey].status == SET && strcmp(h->tab[hashkey].key , key ) == 0 )
    {
        *indice = hashkey;
        return 1;
    }else if(h->tab[hashkey].status == REMOVED && iremoved == -1)
    {
        iremoved = hashkey;
        return -1;
    }
    hashkey = (hashkey + 1 )%h->size;
    i++;
   }
   *indice = hashkey;
//    pas de clé trouvé
   return 0;
}
//La commande insert permet d’ajouter une paire (clé, valeur) au dictionnaire.
void Insert(HashTable * h, char * key, char * val) {
int k;
if(Query(h, key, &k))
{
    // clé existe ecraser sa val
    free(h->tab[k].val);
    h->tab[k].val = strdup(val);
}
else{
    // clé n'existe pas 
    unsigned int hashkey = HashFunction(key, h->size);
      unsigned int i = 1;
    while (h->tab[hashkey].status != EMPTY && i < h->size)
    {
        hashkey = (hashkey + 1 )%h->size;
        i++;
    }
    h->tab[hashkey].key = strdup(key);
      h->tab[hashkey].val = strdup(val);
      h->tab[hashkey].status = SET;
}
}
//La commande delete permet de supprimer un élément du dictionnaire
void Delete(HashTable * h, char * key) {
   int indice;
   if (Query(h, key, &indice)) {
      free(h->tab[indice].key);
      free(h->tab[indice].val);
      h->tab[indice].status = REMOVED;
   }
}
//La commande stats permet d’afficher les statistiques de la table
void Stats(HashTable * h) {
     int i;
     int etatinit = 0, set = 0, removed = 0, empty = 0;
   for (i = 0; i < h->size; i++) {
    etatinit++;
      if (h->tab[i].status == SET) {
        set++;
      } else if (h->tab[i].status == REMOVED) {
        removed++;
      } else {
        empty++;
      }
}
printf("Total: %d, Filled: %d, Removed: %d, Empty: %d\r\n", etatinit, set, removed, empty);
}
//La commande destroy permet de libérer la mémoire
void Destroy(HashTable * h) {
   int i;
   for (i = 0; i < h->size; i++) 
   {
    if (h->tab[i].status == SET || h->tab[i].status == REMOVED) 
    {
         free(h->tab[i].key);
         free(h->tab[i].val);
      }
   }
   free(h->tab);
   free(h);
}

void Print(HashTable * h) {
   int i;
   for (i=0;i<h->size;i++) {
      printf("%d - ",i);
      printf("%s ",Labels[h->tab[i].status]);
      if (h->tab[i].status == SET) {
         printf("- %s ",h->tab[i].key);
         printf("- %s ",h->tab[i].val);
      }
      printf("\n");
   }
}