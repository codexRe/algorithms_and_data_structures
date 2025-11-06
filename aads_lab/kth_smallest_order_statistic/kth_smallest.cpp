#include <bits/stdc++.h>

using namespace std;

int partition(int arr[], int low, int high){
    int pivot = arr[high]; 
    int i = low;
 
    for(int j=low; j<high; j++){
        if(arr[j] <= pivot){
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}


int kthSmallest(int arr[], int low, int high, int k){
    if(k>0 && k<=high-low+1){
        int index = partition(arr, low, high);
        if(index - low == k - 1){
            return arr[index];
        }
        if(index - low > k - 1){
            return kthSmallest(arr, low, index-1, k);
        }
        return kthSmallest(arr, index+1, high, k-index+low - 1);
    }
    return -1;
}

int main() {
    int arr[] = {13, 4, 2, 5, 8, 19, 14, 3, 0, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    int k=6;
    int result=kthSmallest(arr, 0, n-1, k);
    cout<<k<<"-th smallest element is: "<<result<<endl;

    return 0;
}   
