#include<stdio.h>

#define MAX 10000
#define endl printf("\n")

void linear_search(int* arr, int target, int length){
    int i = 0, x = 0;
    for(i; i < length; i++)
        if(arr[i] == target){
            printf("Element FOUND, index = %d\n", i);
            x = 1;
            break; // If you want to search all appearance of target element then remove break
        }
    if (!x){
        printf("Element Not Found!");
        endl;
    }
}

void main(){
    int n;
    printf("\nEnter Array Length (MAX=10000): ");
    scanf("%d", &n);
    endl;

    int arr[n], i = 0, target = -1;
    for (i; i < n; i++){
        printf("Enter Array Element (index = %d): ", i);
        scanf("%d", arr + i);
    }

    printf("\nEnter search target: ");
    scanf("%d", &target);
    endl;

    linear_search(arr, target, n);
}