// Mock 2 (a): hash table with separate chaining, driven by I / D / S commands, then the table.
#include <iostream>
#include <vector>
using namespace std;

// ---- Common setup: chained hash table written by hand ----
struct Node {
    long long key;
    int value;
    Node *next;
    Node(long long k, int v, Node *n) : key(k), value(v), next(n) {}
};

struct HashTable {
    int m;
    vector<Node *> slot;               // slot[i] = head of chain i
    HashTable(int m_) : m(m_), slot(m_, (Node *)0) {}
};

int hashOf(const HashTable &T, long long k) {   // division method, safe for negative keys
    return (int)(((k % T.m) + T.m) % T.m);
}

Node *hashSearch(HashTable &T, long long k) {
    for (Node *x = T.slot[hashOf(T, k)]; x; x = x->next)
        if (x->key == k) return x;
    return 0;
}

void hashInsert(HashTable &T, long long k, int v) {   // new keys go to the HEAD of the chain
    Node *x = hashSearch(T, k);
    if (x) { x->value = v; return; }
    int s = hashOf(T, k);
    T.slot[s] = new Node(k, v, T.slot[s]);
}

bool hashDelete(HashTable &T, long long k) {
    Node **p = &T.slot[hashOf(T, k)];          // p points at the link that leads to the node
    while (*p && (*p)->key != k) p = &(*p)->next;
    if (!*p) return false;
    Node *d = *p;
    *p = d->next;
    delete d;
    return true;
}
// ---- end of common setup ----

int main() {
    ios::sync_with_stdio(false);
    int m, q;
    cin >> m >> q;
    HashTable T(m);
    for (int i = 0; i < q; i++) {
        char op;
        long long k;
        cin >> op >> k;
        if (op == 'I') hashInsert(T, k, 0);
        else if (op == 'D') hashDelete(T, k);
        else cout << (hashSearch(T, k) ? "YES" : "NO") << '\n';
    }
    for (int s = 0; s < m; s++) {
        cout << s << ':';
        for (Node *x = T.slot[s]; x; x = x->next) cout << ' ' << x->key;
        cout << '\n';
    }
    return 0;
}
