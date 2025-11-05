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
        printf("Element Not Found!\n");
    }
}

void main(){
    int n;
    printf("\nLinear Search\n\nEnter Array Length: ");
    scanf("%d", &n);
    printf("\n");

    int arr[n], i = 0, target = -1;
    printf("Enter space separated array elements: ");
    for (i; i < n; i++){
        scanf("%d", arr + i);
    }

    printf("\nEnter search target: ");
    scanf("%d", &target);
    printf("\n");

    linear_search(arr, target, n);
}