#include <stdio.h>

int main() {
    int n;
    int i;
    scanf("%d", &n);

    float tab[n];
    for (i = 0; i < n; i++) {
        scanf("%f", &tab[i]);
    }

    float max_sum = tab[0];
    float current_sum = tab[0];

    for (i = 1; i < n; i++) {
        // Calculate the maximum subarray sum ending at index i
	if (current_sum<0){       //if current_sum(max_sum of the previous element in the array is negative , it's only gonna bring down the value of the current_element)
		current_sum = tab[i];
	}
	else{
		current_sum = current_sum + tab[i]; // else it's going to make it higher
	}
        
        // Update the overall maximum subarray sum
	if (max_sum<current_sum){
		max_sum = current_sum;}
}
       

    printf("%f\r\n", max_sum);

    return 0;
}