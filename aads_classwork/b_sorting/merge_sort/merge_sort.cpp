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
    int n = 0;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << endl;
    int arr[n] = {};
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    int high = sizeof(arr) / sizeof(arr[0]); // Simply, size of array = #elements

    cout << "Original Array : ";
    for(int i = 0; i < high; i++){
        cout << arr[i] << " ";
    }
    cout << '\n';

    merge_sort(arr, 0, high-1);
    
    cout << "After sorting  : ";
    for(int i = 0; i < high; i++){
        cout << arr[i] << " ";
    }
    cout << '\n';
    return 0;
}