#include <iostream>

using namespace std;
#define newline cout << endl;


void merge(int* arr, int s, int m, int e){
    
    int i, j, k;
    int l1 = m - s + 1;
    int l2 = e - m;

    int L[l1], R[l2];

    for (i = 0; i < l1; i++)
        L[i] = arr[s + i];
    for (j = 0; j < l2; j++)
        R[j] = arr[m + 1 + j];

    i = j = 0;
    k = s;
    while (i < l1 && j < l2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < l1)
        arr[k++] = L[i++];

    while (j < l2)
        arr[k++] = R[j++];
}

void merge_sort(int* arr, int start, int end){
    if (start < end) {
        int mid = start + (end - start) / 2;
        merge_sort(arr, start, mid);
        merge_sort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

int main(){
    int arr[] = {19, 8, 3, 24, 5, 6, 2, 12, 34, 5, 665};
    int n = sizeof(arr)/sizeof(int);

    merge_sort(arr, 0, n-1);
    newline
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    newline
    return 0;
}