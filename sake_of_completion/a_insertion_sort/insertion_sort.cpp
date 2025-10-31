#include <iostream>

using namespace std;

void insertion_sort(int* arr, int n){
    int i, j, key;
    for(i = 1; i < n; i++)
        key = arr[i];
        j = i - 1;
        while(j>=0 and arr[j]>key)
            arr[j + 1] = arr[j];
            j -= 1;
        arr[j+ 1] = key;
}

int main(){
    int arr[6] = {10, 203, 2, 12, 43, 90};
    insertion_sort(arr, sizeof(arr) / sizeof(int));
    int i = 0;
    while (i < 6){
        cout << arr[i++] <<" ";
    }
    cout << endl;
    return 0;
}