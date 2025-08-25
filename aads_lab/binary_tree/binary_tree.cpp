// binary tree creation and traversal

#include <iostream>
using namespace std;
#include<vector>

vector<vector<int>>bfs;

class node{
    public:
        int data;
        node* left;
        node* right;
        node(int val) : data(val), left(nullptr), right(nullptr){}
};

int max(int a, int b){
    return (a>b) ? a : b;
}

// height of tree and level order traversal(bfs), but with overhead ["level" variable]
int height(node* root, int level = 0){
    if(root == NULL){
        if (bfs.size() <= level) {
            bfs.resize(level + 1);
        }
        bfs[level].push_back(-1); // place '-1' for null nodes
        return -1;
    }
    
    if(bfs.size() <= level){
        bfs.resize(level + 1);
    }
    
    int h = max(height(root->right, level + 1), 
                height(root->left, level + 1)) + 1;
    bfs[level].push_back(root->data);
    
    return h;
}

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
    node* root = new node(1);
    
    // Level 1 (2 nodes)
    root->left = new node(2);
    root->right = new node(3);
    
    // Level 2 (4 nodes)
    root->left->left = new node(4);
    root->left->right = new node(5);
    root->right->left = new node(6);
    root->right->right = new node(7);
    
    // Level 3 (8 nodes)
    root->left->left->left = new node(8);
    root->left->left->right = new node(9);
    root->left->right->left = new node(10);
    root->left->right->right = new node(11);
    root->right->left->left = new node(12);
    root->right->left->right = new node(13);
    root->right->right->left = new node(14);
    root->right->right->right = new node(15);
    
    // Level 4 (16 nodes)
    root->left->left->left->left = new node(16);
    root->left->left->left->right = new node(17);
    root->left->left->right->left = new node(18);
    root->left->left->right->right = new node(19);
    root->left->right->left->left = new node(20);
    root->left->right->left->right = new node(21);
    root->left->right->right->left = new node(22);
    root->left->right->right->right = new node(23);
    root->right->left->left->left = new node(24);
    root->right->left->left->right = new node(25);
    root->right->left->right->left = new node(26);
    root->right->left->right->right = new node(27);
    root->right->right->left->left = new node(28);
    root->right->right->left->right = new node(29);
    root->right->right->right->left = new node(30);
    root->right->right->right->right = new node(31);
    
    // Level 5 (19 nodes to make total 50)
    root->left->left->left->left->left = new node(32);
    root->left->left->left->left->right = new node(33);
    root->left->left->left->right->left = new node(34);
    root->left->left->left->right->right = new node(35);
    root->left->left->right->left->left = new node(36);
    root->left->left->right->left->right = new node(37);
    root->left->left->right->right->left = new node(38);
    root->left->left->right->right->right = new node(39);
    root->left->right->left->left->left = new node(40);
    root->left->right->left->left->right = new node(41);
    root->left->right->left->right->left = new node(42);
    root->left->right->left->right->right = new node(43);
    root->left->right->right->left->left = new node(44);
    root->left->right->right->left->right = new node(45);
    root->left->right->right->right->left = new node(46);
    root->left->right->right->right->right = new node(47);
    root->right->left->left->left->left = nullptr;
    root->right->left->left->left->right = new node(49);
    root->right->left->left->right->left = new node(50);

    cout << height(root, 0) << endl;
    
    preorder(root);
    cout << endl;
    inorder(root);
    cout << endl;
    postorder(root);
    cout << endl; 

    if (!bfs.empty()) {
        bfs.pop_back();
    }

    for(int i = 0; i < bfs.size(); i++){ // Print Tree Structure :)
        cout << "Level " << i << ": ";
        for(int j = 0; j < bfs[i].size(); j++){
            cout << bfs[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
