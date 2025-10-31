#include <stdio.h>

int temp[1000];

void merge(int* arr, int left, int mid, int right){
    int i, j, k;
    int l = mid - left + 1; // Size of left subarray
    int r = right - mid; // Size of right subarray

    for (i = 0; i < l; i++) // Copy left subarray to temp
        temp[i] = arr[left + i]; // starting from 0 to mid
    
    for (j = 0; j < r; j++) // Copy right subarray to temp
        temp[l + j] = arr[mid + 1 + j]; // starting from mid + 1 to r - 1 (simply, starting after left subarray)
    
    i = 0;    // Index for left subarray in temp
    j = l;    // Index for right subarray in temp 
    k = left; // Index for original array
    
    while (i < l && j < l + r) {
        if (temp[i] <= temp[j]) {
            arr[k++] = temp[i++];
        } else {
            arr[k++] = temp[j++];
        }
    }
    
    // Copy remaining elements
    while (i < l) arr[k++] = temp[i++];
    while (j < l + r) arr[k++] = temp[j++];
}

void merge_sort_dnc(int* arr, int left, int right){
    if (left < right){
        int mid = left + (right - left)/2; // avoiding int type range exceed overflow
        merge_sort_dnc(arr, left, mid);
        merge_sort_dnc(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}