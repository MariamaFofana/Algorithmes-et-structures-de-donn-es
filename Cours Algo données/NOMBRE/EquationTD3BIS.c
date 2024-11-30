#include <stdio.h>
#include <math.h>

int main()
{
    int a, b;
    int solution = 0; 
    scanf("%d %d", &a, &b);

    for (int x = 1; x <= sqrt(a); x++) {
        for (int y = 1; y <= sqrt(a); y++) {
            if (x*x + y*y == a && x*x*x + y*y*y == b) {
                printf("%d %d\r\n", x, y);
                solution = 1; 
            }
        }
    }
    if (!solution) {
        printf("-\r\n");
    }

    return 0;
}