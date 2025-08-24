#include <stdio.h>

#define MAX 10000
#define endl printf("\n");

void countingSort(int* arr, int size) {
  
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
  
    int count[MAX] = {0};
    int res[max+1];

    for (int i = 0; i < size; i++)
        count[arr[i]]++;
  
    for (int i = 1; i <= max; i++) 
        count[i] += count[i - 1];
  
    for (int i = size - 1; i >= 0; i--) 
        res[--count[arr[i]]] = arr[i];
  
    for (int i = 0; i < size; i++) {
        arr[i] = res[i];
    }
}

int main() {
    int n;
    printf("\nEnter Array Length (MAX = 10000): ");
    scanf("%d", &n);
    endl;

    printf("Enter Space Separated Array Elements in SORTED (ASC) Order (MAX VAL = 9999): ");
    int arr[MAX], i = 0, target = -1;
    for (i; i < n; i++){
        scanf("%d", arr + i);
    }
    countingSort(arr, n);
    
    for (i = 0; i < n; i++){
        printf("%d ", *(arr + i));
    }
    endl;
}