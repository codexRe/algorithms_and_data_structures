// Binary Search Iterative
#include<stdio.h>

#define MAX 10000
#define endl printf("\n")

void binary_search(int* arr, int target, int length){

    int i = 0, x = 0;
    int low = 0, high = length - 1, mid = -1;
    
    while (low <= high){
        mid = (low + high) / 2;

        if (arr[mid] == target){
            printf("Element FOUND at index = %d\n", mid);
            x = 1;
            break;
        }
        if (arr[mid] > target)
            high = mid - 1;
        
        else
            low = mid + 1;
    }

    if (!x){
        printf("Element NOT FOUND!");
        endl;
    }
}

void main(){
    int n;
    printf("\nEnter Array Length (MAX=10000): ");
    scanf("%d", &n);
    endl;

    printf("Enter Space Separated Array Elements in SORTED (ASC) Order: ");
    int arr[MAX], i = 0, target = -1;
    for (i; i < n; i++){
        scanf("%d", arr + i);
    }

    printf("\nEnter search target: ");
    scanf("%d", &target);
    endl;

    binary_search(arr, target, n);
}