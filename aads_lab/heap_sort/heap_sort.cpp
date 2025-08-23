#include <iostream>

#define MAX 10000
using namespace std;

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void display_array(int* arr, int n){
    int i = 0;
    cout << endl;
    for (i; i < n; i++)
        cout << arr[i] <<" ";
    cout << endl;
}

void heapify(int* arr, int i, int n){ // Using Maxheap , n = length of array
    int l = 2 * i + 1; // left child
    int r = 2 * (i + 1); // right child
    int max = i;
    
    if (l < n && arr[max] < arr[l])
        max = l;

    if (r < n && arr[max] < arr[r])
        max = r;
    
    if (i != max){
        swap(arr + i, arr + max);
        heapify(arr, max, n);
    }
}

int* build_heap(int* arr, int len){
    for (int i = len/2 - 1; i >= 0; i--)
        heapify(arr, i, len);
    return arr;
}

void heap_sort(int* arr, int len){
    build_heap(arr, len);
    for (int i = len - 1; i > 0; i--){
        swap(arr + 0, arr + i);
        heapify(arr, 0, i);
    }
}

int main(){
    int arr[MAX]={};
    int n = 0, i = 0;
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter space separated " << n << " elements of array: ";
    for(i; i < n; i++){
        cin >> arr[i];
    }

    heap_sort(arr, n);
    display_array(arr, n);
    return 0;
}
