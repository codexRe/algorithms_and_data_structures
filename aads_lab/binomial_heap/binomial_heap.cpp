#include <bits/stdc++.h>
using namespace std;

struct BinomialNode {
    int key;
    int degree;
    BinomialNode* parent;
    BinomialNode* child;
    BinomialNode* sibling;
    BinomialNode(int k) : key(k), degree(0), parent(nullptr), 
                          child(nullptr), sibling(nullptr) {}
};

struct BinomialHeap {
private:
    BinomialNode* head;
    void link(BinomialNode* y, BinomialNode* z) {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree++;
    }

    BinomialNode* merge(BinomialNode* h1, BinomialNode* h2) {
        if (!h1) return h2;
        if (!h2) return h1;
        BinomialNode* head = nullptr;
        BinomialNode** pos = &head;
        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                *pos = h1;
                h1 = h1->sibling;
            } else {
                *pos = h2;
                h2 = h2->sibling;
            }
            pos = &((*pos)->sibling);
        }
        *pos = h1 ? h1 : h2;
        return head;
    }

    BinomialNode* unionHeap(BinomialNode* h1, BinomialNode* h2) {
        BinomialNode* newHead = merge(h1, h2);
        if (!newHead) return nullptr;
        BinomialNode* prev = nullptr;
        BinomialNode* curr = newHead;
        BinomialNode* next = curr->sibling;
        while (next) {
            if (curr->degree != next->degree || 
                (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            } else {
                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    link(next, curr);
                } else {
                    if (prev)
                        prev->sibling = next;
                    else
                        newHead = next;
                    link(curr, next);
                    curr = next;
                }
            }
            next = curr->sibling;
        }
        return newHead;
    }

    BinomialNode* findNode(BinomialNode* h, int key) {
        if (!h) return nullptr;
        if (h->key == key) return h;
        BinomialNode* res = findNode(h->child, key);
        if (res) return res;
        return findNode(h->sibling, key);
    }

    void bubbleUp(BinomialNode* node) {
        while (node->parent && node->key < node->parent->key) {
            swap(node->key, node->parent->key);
            node = node->parent;
        }
    }

    void printHeap_b(BinomialNode* h, int level) {
        if (!h) return;
        for (int i = 0; i < level; i++)
            cout << "  ";
        cout << h->key << " (degree " << h->degree << ")" << endl;
        printHeap_b(h->child, level + 1);
        printHeap_b(h->sibling, level);
    }
    
public:
    BinomialHeap() : head(nullptr) {}
    void insert(int key) {
        BinomialNode* node = new BinomialNode(key);
        head = unionHeap(head, node);
    }

    int getMin() {
        if (!head) return INT_MAX;
        BinomialNode* curr = head;
        int minKey = curr->key;
        while (curr) {
            if (curr->key < minKey)
                minKey = curr->key;
            curr = curr->sibling;
        }
        return minKey;
    }

    int extractMin() {
        if (!head) return INT_MAX;
        BinomialNode* minNode = head;
        BinomialNode* minPrev = nullptr;
        BinomialNode* prev = nullptr;
        BinomialNode* curr = head;
        while (curr->sibling) {
            if (curr->sibling->key < minNode->key) {
                minNode = curr->sibling;
                minPrev = curr;
            }
            curr = curr->sibling;
        }
        if (minPrev)
            minPrev->sibling = minNode->sibling;
        else
            head = minNode->sibling;
        BinomialNode* child = minNode->child;
        BinomialNode* newHead = nullptr;
        while (child) {
            BinomialNode* next = child->sibling;
            child->sibling = newHead;
            child->parent = nullptr;
            newHead = child;
            child = next;
        }
        head = unionHeap(head, newHead);
        int minKey = minNode->key;
        delete minNode;
        return minKey;
    }

    void decreaseKey(int oldKey, int newKey) {
        if (newKey > oldKey) {
            cout << "New key is greater than current key" << endl;
            return;
        }
        BinomialNode* node = findNode(head, oldKey);
        if (!node) {
            cout << "Key not found" << endl;
            return;
        }
        node->key = newKey;
        bubbleUp(node);
    }

    void unionWith(BinomialHeap& other) {
        head = unionHeap(head, other.head);
        other.head = nullptr;
    }

    void deleteKey(int key) {
        decreaseKey(key, INT_MIN);
        extractMin();
    }

    void printHeap() {
        cout << "Binomial Heap:" << endl;
        printHeap_b(head, 0);
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

int main() {
    BinomialHeap h1;
    cout << "Creating a binomial heap (insertion sequence): 12, 7, 25, 15, 28, 33, 41" << endl;
    h1.insert(12);
    h1.insert(7);
    h1.insert(25);
    h1.insert(15);
    h1.insert(28);
    h1.insert(33);
    h1.insert(41);
    h1.printHeap();
    cout << "\nMinimum: " << h1.getMin() << endl;    
    cout << "\nDecreasing 25 to 5" << endl;
    h1.decreaseKey(25, 5);
    cout << "New Minimum: " << h1.getMin() << endl;
    cout << "\nExtracting minimum" << endl;
    cout << "Extracted: " << h1.extractMin() << endl;
    cout << "New minimum: " << h1.getMin() << endl;

    BinomialHeap h2;
    h2.insert(3);
    h2.insert(18);
    cout << "\nUnion with heap containing <3, 18>" << endl;
    h1.unionWith(h2);
    cout << endl;
    h1.printHeap();
    cout << "\nMinimum after union: " << h1.getMin() << endl;

    return 0;
}