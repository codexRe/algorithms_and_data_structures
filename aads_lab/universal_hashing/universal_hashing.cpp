#include <bits/stdc++.h>
using namespace std;

struct UniversalHash {
private:
    int a;          
    int b;          
    int p;          
    int m;

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        }
        return true;
    }

    int nextPrime(int n) {
        while (!isPrime(n)) n++;
        return n;
    }

public:
    UniversalHash(int tableSize, int maxKey) {
        m = tableSize;
        p = nextPrime(maxKey + 1); // as p must be prime and larger than max key

        srand(time(0));
        a = (rand() % (p - 1)) + 1;
        b = rand() % p;           
        cout << "a = " << a << "\n";
        cout << "b = " << b << "\n";
        cout << "p = " << p << "\n";
        cout << "m = " << m << "\n\n";
    }

    int hash(int key) {
        long long mod_p = ((long long)a * key + b) % p;
        int mod_m = mod_p % m;
        return mod_m;
    }
};

struct HashTable {
private:
    vector<vector<int>> table;
    UniversalHash* hashFunc;
    int size;
    
public:
    HashTable(int tableSize, int maxKey) {
        size = tableSize;
        table.resize(size);
        hashFunc = new UniversalHash(tableSize, maxKey);
    }
    
    ~HashTable() {
        delete hashFunc;
    }
    
    void insert(int key) {
        int index = hashFunc->hash(key);
        table[index].push_back(key);
        cout << "Inserted " << key << " at index " << index << "\n";
    }
    
    bool search(int key) {
        int index = hashFunc->hash(key);
        for (int k : table[index]) {
            if (k == key) return true;
        }
        return false;
    }
    
    void display() {
        cout << "\nHash Table Contents: \n";
        for (int i = 0; i < size; i++) {
            cout << "Index " << i << ": ";
            if (table[i].empty()) {
                cout << "empty";
            } else {
                cout << "[ ";
                for (int key : table[i]) {
                    cout << key << " ";
                }
                cout << "]";
            }
            cout << "\n";
        }
    }
    
    void showCollisions() {
        int collisions = 0;
        int maxChainLength = 0;
        int usedSlots = 0;
        
        for (int i = 0; i < size; i++) {
            if (table[i].size() > 0) {
                usedSlots++;
                if (table[i].size() > 1) {
                    collisions += table[i].size() - 1;
                }
                maxChainLength = max(maxChainLength, (int)table[i].size());
            }
        }
        cout << "Used slots: " << usedSlots << "/" << size << "\n";
        cout << "Total collisions: " << collisions << "\n";
        cout << "Max chain length: " << maxChainLength << "\n";
        cout << "Load factor: " << (float)usedSlots / size << "\n";
    }
};

int main() {
    // Create hash table with size m = 12, and p > 10000
    HashTable ht1(12, 10000);
    vector<int> keys = {42, 100, 25, 67, 89, 123, 456, 789, 15, 99};
    for (int key : keys) {
        ht1.insert(key);
    }
    ht1.display();
    cout << "Search 100: " << (ht1.search(100) ? "Found" : "Not Found") << "\n";
    cout << "Search 999: " << (ht1.search(999) ? "Found" : "Not Found") << "\n";
    
    ht1.showCollisions();
    
    cout << "\nSame keys, different random hash functions (randomness illustration):\n\n";
    
    for (int i = 1; i <= 3; i++) {
        UniversalHash hf(10, 1000);
        cout << "Key 42 → " << hf.hash(42) << "\n";
        cout << "Key 100 → " << hf.hash(100) << "\n";
        cout << "Key 25 → " << hf.hash(25) << "\n\n";
        sleep(1);
    }
    
    return 0;
}