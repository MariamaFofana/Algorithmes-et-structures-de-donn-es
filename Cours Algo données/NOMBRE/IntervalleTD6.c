#include <stdio.h>
#include <stdio.h>
// un algorithme qui produit un ensemble IS0 équivalent avec IS avec une aire minimale
int main()
{
    int a1, b1, a2, b2;
    int res = 0;
    scanf("%d %d %d %d", &a1, &b1, &a2, &b2);
    if (b1 >= a2 && b2 >= a1) {
        res = (b1 < b2 ? b1 : b2) - (a1 > a2 ? a1 : a2);
        if (res < 0) {
            res = 0;
        }
    }
    printf("%d\n", res);
    return 0;
}