#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    if (n > 1000) {
        printf("Erreur : le nombre doit être inférieur à 1000.\n");
        return 1; 
    }
    
    while (n != 1) {
        printf("%d\r\n", n); 
        
        if (n % 2 == 0) {
            n = n / 2; 
        } else {
            n = 3 * n + 1;
        }
    }
    
    printf("%d\r\n", n);
    
    return 0;
}
