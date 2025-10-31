#include <stdio.h>

int binary_search_dnc(int* arr, int p, int q, int target){
    if (p == q)
        return (target == arr[p])?p:-1;
    else{
        int mid = (p+q)/2;
        if (arr[mid] == target){
            return mid;
        }
        else{
            if (target < arr[mid])
                return binary_search_dnc(arr, p, mid-1, target);
            else
                return binary_search_dnc(arr, mid+1, q ,target);
        }
    }
}

int main() {
    int arr[] = {1, 23, 45, 76, 99};
    int result = binary_search_dnc(arr, 0, 4, 99);
    printf("%d\n", result);
    return 0;
}