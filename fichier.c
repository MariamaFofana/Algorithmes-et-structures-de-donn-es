#include<stdio.h>
 
int main()
{
   int a, b, somme;
   
   printf("Entrez deux nombres à additionner\n");
   scanf("%d%d", &a, &b);
   
   somme = a + b;
   
   printf("La somme des deux nombres est = %d\n", somme);
   
   return 0;
}