#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct RBNode {
    int data;
    Color color;
    RBNode *left, *right, *parent;
    RBNode(int val) : data(val), color(RED), left(nullptr), 
                      right(nullptr), parent(nullptr) {}
};

struct RBTree {
private:
    RBNode* root;
    RBNode* NIL; // Sentinel node

    void rotateLeft(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(RBNode* y) {
        RBNode* x = y->left;
        y->left = x->right;
        if (x->right != NIL)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
        x->right = y;
        y->parent = x;
    }
    
    void fixInsert(RBNode* z) { // Fix violations after insertion
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode* y = z->parent->parent->right; // Uncle
                if (y->color == RED) {
                    // Case 1: Uncle is red
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        // Case 2: z is right child
                        z = z->parent;
                        rotateLeft(z);
                    }
                    // Case 3: z is left child
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            } else {
                RBNode* y = z->parent->parent->left; // Uncle
                if (y->color == RED) {
                    // Case 1: Uncle is red
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        // Case 2: z is left child
                        z = z->parent;
                        rotateRight(z);
                    }
                    // Case 3: z is right child
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
    void transplant(RBNode* u, RBNode* v) { // Transplant subtree
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    RBNode* minimum(RBNode* node) {
        while (node->left != NIL)
            node = node->left;
        return node;
    }
    
    // Fix violations after deletion
    void fixDelete(RBNode* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBNode* w = x->parent->right; // Sibling
                
                if (w->color == RED) {
                    // Case 1: Sibling is red
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    // Case 2: Sibling's children are black
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        // Case 3: Sibling's right child is black
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    // Case 4: Sibling's right child is red
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            } else {
                RBNode* w = x->parent->left; // Sibling
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void deleteNode(RBNode* z) {
        RBNode* y = z;
        RBNode* x;
        Color yOriginalColor = y->color;
        
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        
        delete z;
        
        if (yOriginalColor == BLACK)
            fixDelete(x);
    }

    RBNode* searchNode(RBNode* node, int key) {
        if (node == NIL || key == node->data)
            return node;
        
        if (key < node->data)
            return searchNode(node->left, key);
        return searchNode(node->right, key);
    }

    void inorderTraversal(RBNode* node) {
        if (node != NIL) {
            inorderTraversal(node->left);
            cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
            inorderTraversal(node->right);
        }
    }
    
public:
    RBTree() {
        NIL = new RBNode(0);
        NIL->color = BLACK;
        root = NIL;
    }
    void insert(int key) {
        RBNode* z = new RBNode(key);
        z->left = NIL;
        z->right = NIL;
        RBNode* y = nullptr;
        RBNode* x = root;
        
        while (x != NIL) {
            y = x;
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        
        if (y == nullptr)
            root = z;
        else if (z->data < y->data)
            y->left = z;
        else
            y->right = z;
        
        if (z->parent == nullptr) {
            z->color = BLACK;
            return;
        }
        if (z->parent->parent == nullptr)
            return;
        
        fixInsert(z);
    }
    void remove(int key) {
        RBNode* z = searchNode(root, key);
        if (z != NIL)
            deleteNode(z);
    }

    void inorder() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    RBTree tree;
    cout << "Inserting: 7, 3, 18, 10, 22, 8, 11, 26" << endl;
    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    cout << "Inorder traversal (R=Red, B=Black): ";
    tree.inorder();
    cout << "\nDeleting 18" << endl;
    tree.remove(18);
    cout << "Inorder traversal: ";
    tree.inorder();
    return 0;
}