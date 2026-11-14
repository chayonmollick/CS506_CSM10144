// Template: hash table with separate chaining, hand-written (no STL containers).
// Input : m q, then q lines, each one of   I x | S x | D x | P
// Output: I -> nothing, S -> FOUND / NOT FOUND, D -> DELETED / NOT FOUND,
//         P -> m lines "i: k1 k2 ..." (chain i from head to tail)
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* next;
};

struct HashTable {
    int m;      // number of slots
    Node** T;   // T[i] = head of chain i (NULL = empty chain)
};

int hashFn(int k, int m) { return ((k % m) + m) % m; }  // division method, safe for k < 0

void initTable(HashTable& H, int m) {
    H.m = m;
    H.T = new Node*[m];
    for (int i = 0; i < m; i++) H.T[i] = NULL;
}

// CHAINED-HASH-SEARCH: walk the one chain the key can be in
Node* chainSearch(const HashTable& H, int k) {
    for (Node* p = H.T[hashFn(k, H.m)]; p != NULL; p = p->next)
        if (p->key == k) return p;
    return NULL;
}

// CHAINED-HASH-INSERT: new node goes at the HEAD of its chain (duplicates ignored)
bool chainInsert(HashTable& H, int k) {
    if (chainSearch(H, k) != NULL) return false;
    int j = hashFn(k, H.m);
    Node* x = new Node;
    x->key = k;
    x->next = H.T[j];   // old head becomes second
    H.T[j] = x;
    return true;
}

// CHAINED-HASH-DELETE: unlink the node holding k (keep a pointer to the previous node)
bool chainDelete(HashTable& H, int k) {
    int j = hashFn(k, H.m);
    Node* prev = NULL;
    Node* cur = H.T[j];
    while (cur != NULL && cur->key != k) { prev = cur; cur = cur->next; }
    if (cur == NULL) return false;          // not present
    if (prev == NULL) H.T[j] = cur->next;   // deleting the head
    else prev->next = cur->next;
    delete cur;
    return true;
}

void printTable(const HashTable& H) {
    for (int i = 0; i < H.m; i++) {
        cout << i << ":";
        for (Node* p = H.T[i]; p != NULL; p = p->next) cout << " " << p->key;
        cout << "\n";
    }
}

void freeTable(HashTable& H) {
    for (int i = 0; i < H.m; i++)
        while (H.T[i] != NULL) { Node* t = H.T[i]; H.T[i] = t->next; delete t; }
    delete[] H.T;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int m, q;
    cin >> m >> q;
    HashTable H;
    initTable(H, m);
    while (q--) {
        char op;
        cin >> op;
        if (op == 'P') { printTable(H); continue; }
        int x;
        cin >> x;
        if (op == 'I') chainInsert(H, x);
        else if (op == 'S') cout << (chainSearch(H, x) != NULL ? "FOUND" : "NOT FOUND") << "\n";
        else if (op == 'D') cout << (chainDelete(H, x) ? "DELETED" : "NOT FOUND") << "\n";
    }
    freeTable(H);
    return 0;
}
