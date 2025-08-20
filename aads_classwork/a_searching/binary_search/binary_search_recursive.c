// Binary Search Iterative
#include<stdio.h>

#define MAX 10000
#define endl printf("\n")

int binary_search(int* arr, int target, int low, int high){

    int i = 0, x = 0;
    int mid = -1;
    
    if (low > high){
        printf("Element NOT FOUND!");
        endl;
        return -1;
    }

    mid = (low + high) / 2;
    
    if (arr[mid] == target){
        printf("Element FOUND at index = %d\n", mid);
        return 0;
    }
    
    if (arr[mid] > target)
        binary_search(arr, target, low, mid - 1);

    else
        binary_search(arr, target, mid + 1, high);
}

void main(){
    int n;
    printf("\nEnter Array Length (MAX=10000): ");
    scanf("%d", &n);
    endl;

    printf("Enter Space Separated Array Elements in SORTED (ASC) Order: ");
    int arr[n], i = 0, target = -1;
    for (i; i < n; i++){
        scanf("%d", arr + i);
    }

    printf("\nEnter search target: ");
    scanf("%d", &target);
    endl;

    binary_search(arr, target, 0, n-1);
}