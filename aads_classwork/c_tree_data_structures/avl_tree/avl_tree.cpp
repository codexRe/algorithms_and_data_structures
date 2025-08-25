#include <iostream>

using namespace std;

class node{
    public:
        int data;
        node* left;
        node* right;
        int height;
        node(int val) : data(val), left(nullptr), right(nullptr), height(0){}
};

int max(int a, int b){
    return (a>b) ? a : b;
}

int min(int a, int b){
    return (a>b) ? b : a;
}

int height(node* root){
    if(root == NULL)
        return 0;
    return max(height(root->right), height(root->left)) + 1;
}

int balance_factor(node* root){
    if(root == nullptr)
        return 0;
    return height(root->left) - height(root->right);
}

node* min_node(node* root){
    if(root->left == nullptr)
        return root;
    return min_node(root->left);
}

node* ll_rotation(node* root){
    node* new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    return new_root;
}

node* rr_rotation(node* root){
    node* new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    return new_root;
}

void avl_tree_insertion();
void avl_tree_deletion();

// DFS Traversals
void preorder(node* root){
    if (root == nullptr) return;

    cout << root -> data << " ";
    preorder(root -> left);
    preorder(root -> right);
}

void inorder(node* root){
    if (root == nullptr) return;

    inorder(root -> left);
    cout << root -> data << " ";
    inorder(root -> right);
}

void postorder(node* root){
    if (root == nullptr) return;

    postorder(root -> left);
    postorder(root -> right);
    cout << root -> data << " ";
}


int main(){
    return 0;
}