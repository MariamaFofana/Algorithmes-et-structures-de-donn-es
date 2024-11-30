#include <stdio.h>
#include <math.h>

int main() {
    int LIM;
    scanf("%d", &LIM);

    int compteur = 0;

    // Vérifier chaque nombre N de 2 à LIM
    for (int N = 2; N <= LIM; N++) {
        int sum_divisors = 0;

        // Trouver les diviseurs de N
        for (int i = 2; i <= sqrt(N); i++) {
            if (N % i == 0) {
                sum_divisors += i;        
                if (i != N / i) {         
                    sum_divisors += N / i; 
                }
            }
        }

        // Vérifier si la somme des diviseurs non triviaux est >= N
        if (sum_divisors >= N) {
            compteur++;
        }
    }

    // Afficher le nombre de nombres forts
    printf("%d\r\n", compteur);
    return 0;
}
