#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

struct AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    void updateHeight(Node* node) {
        if (node)
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }
    
    Node* insertNode(Node* node, int key) {
        // Standard BST insertion
        if (!node)
            return new Node(key);

        if (key < node->data)
            node->left = insertNode(node->left, key);
        else if (key > node->data)
            node->right = insertNode(node->right, key);
        else
            return node; // Duplicate keys not allowed

        updateHeight(node);
        int balance = getBalance(node);
        
        // LL
        if (balance > 1 && key < node->left->data)
            return rotateRight(node);
        
        // RR
        if (balance < -1 && key > node->right->data)
            return rotateLeft(node);
        
        // LR
        if (balance > 1 && key > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // RL
        if (balance < -1 && key < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }
    
    Node* deleteNode(Node* node, int key) {
        if (!node)
            return node;
        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            // Node with one child or no child
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                
                if (!temp) { // if no child
                    temp = node;
                    node = nullptr;
                } else // if one child
                    *node = *temp;
                
                delete temp;
            } else {
                // if node has two children
                Node* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }
        
        if (!node)
            return node;

        updateHeight(node);

        int balance = getBalance(node);
        
        // LL
        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);
        
        // LR
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // RR
        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);
        
        // RL
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    // Inorder traversal helper
    void inorderTraversal(Node* node) {
        if (node) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(int key) {
        root = insertNode(root, key);
    }
    
    void remove(int key) {
        root = deleteNode(root, key);
    }
    
    void inorder() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    AVLTree tree;
    cout << "Inserting: 10, 20, 30, 40, 50, 25" << endl;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    cout << "Inorder traversal: ";
    tree.inorder();
    
    cout << "\nDeleting 40" << endl;
    tree.remove(40);
    cout << "Inorder traversal: ";
    tree.inorder();
    
    return 0;
}