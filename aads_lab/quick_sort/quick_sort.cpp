#include <bits/stdc++.h>

using namespace std;

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Naive partition is stable but other two aren't, but other two are efficient

int partition(int* arr, int low, int high){ // Hoare's Partition - most efficient
    int x = arr[low];
    int i = low;

    for (int j = low + 1; j <= high; j++) {
        if (arr[j] <= x){  // flipping this sign will change the order(ascending: <= /descending: >=) of output
            swap(arr + ++i, arr + j);
        }
    }
    swap (arr + low, arr + i);
    return i;
}

int random_partition(int* arr, int low, int high){
    srand(time(NULL));
    int random = low + rand() % (high - low);
    swap(arr[random], arr[low]);
    return partition(arr, low, high);
}

// int partition(int* arr, int low, int high) { // commonly used one (from internet): Lomuto’s Partition
//     int pivot = arr[high];
//     int i = low - 1;

//     for (int j = low; j < high; j++) {
//         if (arr[j] <= pivot) {
//             i++;
//             swap(arr + i, arr + j);
//         }
//     }
//     swap(arr + i + 1, arr + high);
//     return i + 1;
// }

void quicksort(int* arr, int low, int high){
    if(low < high){
        int i = random_partition(arr, low, high); // 'i' is pivot element
        quicksort(arr, low, i-1);
        quicksort(arr, i+1, high);
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

    quicksort(arr, 0, high-1);
    
    cout << "After sorting  : ";
    for(int i = 0; i < high; i++){
        cout << arr[i] << " ";
    }
    cout << '\n';
    return 0;
}