#include<bits/stdc++.h>

using namespace std;

class Node {
public:
    int key;
    int listLevel;
    Node** forward; // Array of pointers to the next node at each level

    Node(int k, int level): key(k), listLevel(level){ // initialize key and allocate forward pointers
        forward = new Node*[level + 1];
        for (int i = 0; i <= level; i++) {
            forward[i] = nullptr;
        }
    }

    ~Node() { // deallocate memory for forward pointers
        delete[] forward;
    }
};

int coinFlip(double p, int maxLevel){
    int level = 0;
    while((double)rand()/RAND_MAX <= p && level < maxLevel) // if (double)rand()/RAND_MAX <= p then Heads, increase level else tails: stop process
        level++;

    return level;
}

class SkipList {
    public:
        int maxLevel;
        float p;
        int level;
        Node* head;
        SkipList(int maxLevel, float p)
            : maxLevel(maxLevel), p(p), level(0) {
            head = new Node(-1, maxLevel); // dummy head
        }
};

void insertIntoSkipList(SkipList* list, int key){
    int level = coinFlip(list->p, list->maxLevel);

    Node* update[list->maxLevel + 1];
    Node* y = new Node(key, level);
    Node* x = list->head;

    for(int k = level; k >= 0; k--){
        if (!x)
            list->head->forward[k] = y;
        else{
            Node* z = x->forward[k+1];
            while(z && key > z->key){
                x = z;
                z ;
            }
        }
    }

}


int main(){
    // cout << "Only one rule, keys are >= 0\n\n";
    cout << coinFlip(0.5, 16) << endl;
    return 0;
}