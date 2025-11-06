#include<bits/stdc++.h>
using namespace std;

struct FibNode {
    int key;
    int degree;
    bool mark;
    FibNode* parent;
    FibNode* child;
    FibNode* left;
    FibNode* right;
    FibNode(int k) : key(k), degree(0), mark(false), 
                     parent(nullptr), child(nullptr) {
        left = right = this;
    }
};

struct FibonacciHeap {
private:
    FibNode* minNode;
    int numNodes;

    void link(FibNode* y, FibNode* x) {
        // Remove y from root list
        y->left->right = y->right;
        y->right->left = y->left;
        
        // Make y child of x
        y->parent = x;
        
        if (x->child == nullptr) {
            x->child = y;
            y->left = y->right = y;
        } else {
            y->left = x->child;
            y->right = x->child->right;
            x->child->right->left = y;
            x->child->right = y;
        }
        x->degree++;
        y->mark = false;
    }
    
    
    void consolidate() {    // Consolidate trees after extract-min
        int maxDegree = (int)(log(numNodes) / log(2)) + 1;
        FibNode** degreeTable = new FibNode*[maxDegree + 1];
        
        for (int i = 0; i <= maxDegree; i++)
            degreeTable[i] = nullptr;
        
        // Create list of root nodes
        FibNode* curr = minNode;
        int numRoots = 0;
        if (curr) {
            numRoots++;
            curr = curr->right;
            while (curr != minNode) {
                numRoots++;
                curr = curr->right;
            }
        }
        
        // Process each root
        while (numRoots > 0) {
            int d = curr->degree;
            FibNode* next = curr->right;
            
            while (degreeTable[d] != nullptr) {
                FibNode* other = degreeTable[d];
                
                if (curr->key > other->key)
                    swap(curr, other);
                
                link(other, curr);
                degreeTable[d] = nullptr;
                d++;
            }
            
            degreeTable[d] = curr;
            curr = next;
            numRoots--;
        }
        
        // Rebuild root list
        minNode = nullptr;
        
        for (int i = 0; i <= maxDegree; i++) {
            if (degreeTable[i] != nullptr) {
                if (minNode == nullptr) {
                    minNode = degreeTable[i];
                    minNode->left = minNode->right = minNode;
                } else {
                    degreeTable[i]->left = minNode;
                    degreeTable[i]->right = minNode->right;
                    minNode->right->left = degreeTable[i];
                    minNode->right = degreeTable[i];
                    
                    if (degreeTable[i]->key < minNode->key)
                        minNode = degreeTable[i];
                }
            }
        }
        
        delete[] degreeTable;
    }
    
    // Cut node from parent
    void cut(FibNode* x, FibNode* y) {
        // Remove x from child list of y
        if (x->right == x) {
            y->child = nullptr;
        } else {
            x->left->right = x->right;
            x->right->left = x->left;
            if (y->child == x)
                y->child = x->right;
        }
        y->degree--;
        // Add x to root list
        x->left = minNode;
        x->right = minNode->right;
        minNode->right->left = x;
        minNode->right = x;
        x->parent = nullptr;
        x->mark = false;
    }

    void cascadingCut(FibNode* y) {
        FibNode* z = y->parent;
        if (z != nullptr) {
            if (!y->mark) {
                y->mark = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

    FibNode* findNode(FibNode* node, int key) {
        if (node == nullptr) return nullptr;
        FibNode* curr = node;
        do {
            if (curr->key == key)
                return curr;
            FibNode* result = findNode(curr->child, key);
            if (result != nullptr)
                return result;
            curr = curr->right;
        } while (curr != node);
        return nullptr;
    }

    void printHeap_b(FibNode* node, int level) {
        if (!node) return;
        FibNode* curr = node;
        do {
            for (int i = 0; i < level; i++)
                cout << "  ";
            cout << curr->key << " (deg:" << curr->degree 
                 << ", mark:" << (curr->mark ? "T" : "F") << ")" << endl;
            printHeap_b(curr->child, level + 1);
            curr = curr->right;
        } while (curr != node);
    }
    
public:
    FibonacciHeap() : minNode(nullptr), numNodes(0) {}

    void insert(int key) {
        FibNode* node = new FibNode(key);
        if (minNode == nullptr) {
            minNode = node;
        } else {
            node->left = minNode;
            node->right = minNode->right;
            minNode->right->left = node;
            minNode->right = node;
            if (node->key < minNode->key)
                minNode = node;
        }
        numNodes++;
    }

    int getMin() {
        return minNode ? minNode->key : INT_MAX;
    }

    int extractMin() {
        FibNode* z = minNode;
        if (z != nullptr) {
            
            if (z->child != nullptr) {      // Add all children to root list
                FibNode* child = z->child;
                do {
                    FibNode* next = child->right;
                    child->left = minNode;
                    child->right = minNode->right;
                    minNode->right->left = child;
                    minNode->right = child;
                    child->parent = nullptr;
                    
                    child = next;
                } while (child != z->child);
            }
            // Remove z from root list
            z->left->right = z->right;
            z->right->left = z->left;
            if (z == z->right) {
                minNode = nullptr;
            } else {
                minNode = z->right;
                consolidate();
            }            
            numNodes--;
            int minKey = z->key;
            delete z;
            return minKey;
        }        
        return INT_MAX;
    }
    
    void decreaseKey(int oldKey, int newKey) {
        if (newKey > oldKey) {
            cout << "New key is greater than current key" << endl;
            return;
        }        
        FibNode* x = findNode(minNode, oldKey);
        if (x == nullptr) {
            cout << "Key not found" << endl;
            return;
        }        
        x->key = newKey;
        FibNode* y = x->parent;        
        if (y != nullptr && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }        
        if (x->key < minNode->key)
            minNode = x;
    }

    void deleteKey(int key) {
        decreaseKey(key, INT_MIN);
        extractMin();
    }

    void unionWith(FibonacciHeap& other) {
        if (other.minNode == nullptr)
            return;        
        if (minNode == nullptr) {
            minNode = other.minNode;
        } else {
            FibNode* temp = minNode->right;
            minNode->right = other.minNode->right;
            other.minNode->right->left = minNode;
            other.minNode->right = temp;
            temp->left = other.minNode;
            
            if (other.minNode->key < minNode->key)
                minNode = other.minNode;
        }        
        numNodes += other.numNodes;
        other.minNode = nullptr;
        other.numNodes = 0;
    }

    void printHeap() {
        cout << "Fibonacci Heap:" << endl;
        printHeap_b(minNode, 0);
    }
    
    bool isEmpty() {
        return minNode == nullptr;
    }
};

int main() {
    FibonacciHeap heap;
    cout << "Inserting: 10, 20, 30, 15, 25, 5" << endl;
    heap.insert(10);
    heap.insert(20);
    heap.insert(30);
    heap.insert(15);
    heap.insert(25);
    heap.insert(5);
    cout << endl;
    heap.printHeap();
    cout << "Minimum: " << heap.getMin() << endl;
    cout << "\nDecreasing 30 to 3" << endl;
    heap.decreaseKey(30, 3);
    cout << "New minimum: " << heap.getMin() << endl;
    cout << endl;
    heap.printHeap();
    cout << "Extracting minimum: " << heap.extractMin() << endl;
    cout << "New minimum: " << heap.getMin() << endl;
    cout << endl;
    heap.printHeap();
    cout << "\nDeleting 15" << endl;
    heap.deleteKey(15);
    
    heap.printHeap();
    
    return 0;
}