// Note: Bucket sort works when data is uniformly distributed and you can make proper buckets by range.
#include <iostream>
using namespace std;

#define bucket_count 10

// Quicksort start
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* arr, int low, int high){ // Horae's Partition
    int x = arr[low];
    int i = low;

    for (int j = low + 1; j <= high; j++) {
        if (arr[j] <= x){  // flipping this sign will change the order(ascending: <= /descending: >=) of output
            i++;
            swap(arr + i, arr + j);
        }
    }
    swap (arr + low, arr + i);
    return i;
}

void quicksort(int* arr, int low, int high){
    if(low < high){
        int i = partition(arr, low, high); // 'i' is pivot element
        quicksort(arr, low, i-1);
        quicksort(arr, i+1, high);
    }
}

void print_array(int* arr, int n){
    int i;
    for (i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}

// Using max range of data = {-99 to +99}, and max size of array = 100 as well, because bucket sort works well in case of small input size which saves us hassle of extra space (considering space complexity)

void bucket_sort(int* arr, int n){
    int positive_bucket[bucket_count][n] = {}, p_track[10] = {}; 
    int negative_bucket[bucket_count][n] = {}, n_track[10] = {};
    int zero_count = 0;

    int i;

    for(i = 0; i < n; i++){
        if(arr[i] >= 0){
            if(arr[i] > 0){
                int bucket_num = arr[i]/10;
                positive_bucket[bucket_num][p_track[bucket_num] ++] = arr[i];
            }
            else if(arr[i] == 0){
                zero_count ++;
            }
        }
        else {
            int bucket_num = -arr[i]/10;
            negative_bucket[bucket_num][n_track[bucket_num] ++] = arr[i];
        }
    }

    for(i = 0; i < bucket_count; i++){
        if (p_track[i] > 1) 
            quicksort(positive_bucket[i], 0, p_track[i] - 1);
        if (n_track[i] > 1) 
            quicksort(negative_bucket[i], 0, n_track[i] - 1);
    }

    int k = 0;

    // negatives go first (largest bucket index to smallest for ascending order)
    for (i = 9; i >= 0; i--) {
        for (int j = 0; j < n_track[i]; j++) {
            arr[k++] = negative_bucket[i][j];
        }
    }

    // zeros
    for (i = 0; i < zero_count; i++) {
        arr[k++] = 0;
    }

    // positives (smallest bucket index to largest)
    for (i = 0; i < 10; i++) {
        for (int j = 0; j < p_track[i]; j++) {
            arr[k++] = positive_bucket[i][j];
        }
    }
    print_array(arr, n);
}

int main(){

    int n, i;
    cout << "Enter array size: ";
    cin >> n;

    int arr[n];

    cout << "Enter array elements: ";
    for(i = 0; i < n; i++){
        cin >> arr[i];
    }

    cout << "\nArray elements: ";
    print_array(arr, n);

    // Validation
    bool valid = true;
    for (int i = 0; i < n; ++i) {
        if (!(arr[i] > -100 && arr[i] < 100)) { // strict bounds: excludes -100 and 100
            cout << "Value out of bounds at index " << i << ": " << arr[i] << "\n";
            cout <<"Permissible range of data is: [-99 <= (X:int) <= 99]";
            valid = false;
            break;
        }
    }
    if (!valid) return 1;

    cout << "\nAfter sorting: ";
    bucket_sort(arr, n);

    return 0;
}

/*
Testcase 1:

90

56 -30 -66 84 90 -41 -26 -75 -47 0 -6 -53 43 -69 83 9 -8 19 -5 -1 -54 -65 85 16 70 -86 -84 77 -42 -87 -40 -88 -13 44 -61 -28 -55 0 89 -16 -4 5 41 -51 40 -3 50 30 10 -78 -8 64 -10 -25 45 -97 75 21 31 71  -63 93 -43 15 -48 42 -12 32 -46 -59 -99 -23 -68 18 -17 -76 -67 -49 47 -96 65 90 -2 -21 72 4 0 -18 -99 87
*/