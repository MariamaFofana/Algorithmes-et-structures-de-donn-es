#include <stdio.h>
int factorielle (int k );
int main() {
    int n=0;
    int resultat;
    scanf("%d",&n);
    resultat = factorielle(n);
  printf("%d\r\n",resultat);
  return 0;
}

int factorielle(int k){
    if (k >0){
        if ( k==1) {
            return 1;
        }
        else {
            return k*factorielle(k-1);
        }
    }
    else{
        return 0;
    }
}