#include <stdio.h>

typedef struct{
    int min;
    int max;
} MinMax;

MinMax minmax_dnc(int* arr, int p, int q){
    MinMax result, left, right;
    int mid;
    
    if (p==q){
        result.min = result.max = arr[p];
        return result;
    }
    else if(p == q - 1){
        result.max = (arr[p] > arr[q])? arr[p] : arr[q];
        result.min = arr[p] ^ arr[q] ^ result.max;
        return result;
    }
    else{
        mid = (p+q)/2;
        left = minmax_dnc(arr, p, mid);
        right = minmax_dnc(arr, mid+1, q);
        result.max = (left.max > right.max) ? left.max : right.max;
        result.min = (left.min < right.min) ? left.min : right.min;
        return result;
    }
}

int main() {
    int arr[] = {10, 1, 23, 45, 76};
    MinMax result = minmax_dnc(arr, 0, 4);
    printf("min = %d, max = %d", result.min, result.max);
    return 0;
}