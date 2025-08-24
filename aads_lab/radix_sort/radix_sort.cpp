#include <iostream>

using namespace std;

void radix_sort(int* arr, int n){
    
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    int res[n] = {0}, e = 1, i; // e = exponent, i = iterator

    while(max/e > 0){
        // counting sort (for sorting less number of elements, it does the job in O(n) space and time)
        int count[10] = {0};

        for(i = 0; i < n; i++)
            ++count[(arr[i] / e) % 10];
        
        for(i = 1; i < 10; i++)
            count[i] += count[i-1];
        
        for(i = n - 1; i >= 0; i--)
            res[--count[(arr[i] / e) % 10]] = arr[i];
        
        for(i = 0; i < n; i++)
            arr[i] = res[i];
        
        e *= 10;
    }
}

int main(){

    int arr[]= {0, 1, 123, 1342, 312, 440, 21, 349, 1290, 32};
    int n = sizeof(arr) / sizeof(int);
    radix_sort(arr, n);

    for(int i = 0; i < 10; i++)
        cout << arr[i] << " ";
    cout << "\n\n";
    return 0;
}