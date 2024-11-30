#include <stdio.h>

int main() {
    int X[1000]; 
    int n = 0;   
    while (1) {
        int x;
        scanf("%d", &x);
        if (x == -1) {
            break; 
        }
        X[n++] = x; 
    }
    int is_palindrome = 1; 
    for (int i = 0; i < n / 2; i++) {
        if (X[i] != X[n - i - 1]) { 
            is_palindrome = 0; 
            break;
        }
    }
    printf("%d\r\n", is_palindrome);
    return 0;
}