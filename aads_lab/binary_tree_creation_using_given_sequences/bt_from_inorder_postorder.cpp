#include <iostream>

using namespace std;

class node{
    public:
        int data;
        node* left;
        node* right;
        node(int val) : data(val), left(nullptr), right(nullptr){}
};

// int binary_search(int* arr, int target, int low, int high){ // works in case of bst

//     int i = 0, x = 0;
//     int mid = -1;
    
//     while (low <= high){
//         mid = (low + high) / 2;

//         if (arr[mid] == target){
//             return mid;
//         }
//         if (arr[mid] > target)
//             high = mid - 1;
        
//         else
//             low = mid + 1;
//     }
//     return -1;
// }

int linear_search(int *arr, int start, int end, int target){
    for (int i=start; i<=end; i++){
        if (arr[i] == target)
            return i;
    }
    return -1;
}

node* preorder(int* inorder, int* postorder, int in_start, int in_end, int post_start, int post_end){
    if (in_start > in_end || post_start >  post_end){
        cout << "null" << endl;
        return nullptr;
    }
    node* root = new node(postorder[post_end]);
    int index = linear_search(inorder, in_start, in_end, root->data);
    cout << root->data << "\n";
    root->left = preorder(inorder, postorder, in_start, index-1, post_start,  post_start + index - in_start - 1); // lst
    root-> right = preorder(inorder, postorder, index + 1, in_end, index - in_start + post_start, post_end - 1); // rst
    return root;
}

// todo in leetcode:
// add bfs element, use size of array instead of range :_)

int main(){
    // int postorder[] = {7, 9, 8, 11, 13, 12, 10};
    // int inorder[] = {7, 8, 9, 10, 11, 12, 13};
    int postorder[] = {9, 18, 12, 10};
    int inorder[] = {9, 18, 10, 12};

    int n = sizeof(inorder)/sizeof(int);
    preorder(inorder, postorder, 0, n-1, 0, n-1); // 0 to n-1 | total = n
}