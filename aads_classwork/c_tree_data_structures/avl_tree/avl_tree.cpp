#include <iostream>

class node{
    public:
        int data;
        node* left;
        node* right;
        node(int val) : data(val), left(nullptr), right(nullptr){}
};


int height();
int balance_factor();

void avl_tree_insertion();
void avl_tree_deletion();
void bfs_traversal();
void dfs_preorder();
void dfs_inorder();
void dfs_postorder();


int main();