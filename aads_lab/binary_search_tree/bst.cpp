#include <iostream>
using namespace std;
#include<vector>

vector<vector<int>>bfs;

struct node{
        int data;
        node* left;
        node* right;
        node(int data): data(data), left(nullptr), right(nullptr){}
};

int max(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}

// height and level order traversal(bfs), but with overhead ["level" variable]
int height(node* root, int level = 0){
    if(root == nullptr){
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

// Insertion
node* insert(struct node* root, int item){
    if(root == nullptr){
        node* newnode = new node(0);
        newnode->data = item;
        newnode->left = newnode->right = nullptr;
        return newnode;
    }

    if (root->data > item){
        root -> left = insert(root->left, item);
    }

    else if (root->data <= item){
        root -> right = insert(root->right, item);
    }
    return root;
}

// Search
node* search(node* root, int item){
    if (root == nullptr || root->data == item)
        return root;
    if (root->data < item)
        return search(root->right, item);
    else
        return search(root->left, item);
}

// Deletion
node* delete_(node* root, int key) {
    if (root == nullptr) return root;

    if (key < root->data) {
        root->left = delete_(root->left, key);
    } 
    else if (key > root->data) {
        root->right = delete_(root->right, key);
    } 
    else {
        if (root->left == nullptr && root->right == nullptr) { // No child
            delete root;
            return nullptr;
        }

        else if (root->left == nullptr) { // may have right child
            node* temp = root->right;
            delete root;
            return temp;
        } 
        else if (root->right == nullptr) { // or may have left child, then replace by only child
            node* temp = root->left;
            delete root;
            return temp;
        }

        else { // or both child, then inorder successor
            node* succ = root->right;
            while (succ->left != nullptr)
                succ = succ->left;

            root->data = succ->data;

            root->right = delete_(root->right, succ->data);
        }
    }
    return root;
}

// max
int max(node* ptr){
    while (ptr->right != nullptr)
        ptr = ptr->right;
    return ptr->data;
}

// min
int min(node* ptr){
    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr->data;
}

int main(){
    node* root = new node(35);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 60);
    root = insert(root, 50);
    root->right->right->right = new node(70);

    preorder(root);
    cout << endl;
    inorder(root);
    cout << endl;
    postorder(root);
    cout << endl;

    cout << height(root, 0) << endl;

    for(int i = 0; i < bfs.size(); i++){
        cout << "Level " << i << ": ";
        for(int j = 0; j < bfs[i].size(); j++){
            cout << bfs[i][j] << " ";
        }
        cout << endl;
    }

    (search(root, 50) != NULL)? cout << "Element found\n": cout << "Element not found\n";
    (search(root, 100) != NULL)? cout << "Element found\n": cout << "Element not found\n";
    (delete_(root, 30) != NULL)? cout << "Element Delete Success\n": cout << "Element Delete Unsuccess\n";

    bfs.clear(); // Don't forget to clear the bfs vector :)
    cout << height(root, 0) << endl;

    for(int i = 0; i < bfs.size(); i++){
        cout << "Level " << i << ": ";
        for(int j = 0; j < bfs[i].size(); j++){
            cout << bfs[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Max Element: " << max(root) << "\n";
    cout << "Min Element: " << min(root) << "\n";


    return 0;
}