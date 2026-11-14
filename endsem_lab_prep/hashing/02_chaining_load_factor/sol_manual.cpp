// 02. Chaining with search/delete queries, load factor, longest chain: hand-written lists
#include <iomanip>
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* next;
};

int m;
Node** T;          // T[i] = head of chain i
int stored = 0;    // n = number of keys in the table

int h(int k) { return ((k % m) + m) % m; }

Node* chainSearch(int k) {
    for (Node* p = T[h(k)]; p != NULL; p = p->next)
        if (p->key == k) return p;
    return NULL;
}

void chainInsert(int k) {               // at the head; duplicates ignored
    if (chainSearch(k) != NULL) return;
    Node* x = new Node;
    x->key = k;
    x->next = T[h(k)];
    T[h(k)] = x;
    stored++;
}

bool chainDelete(int k) {
    Node* prev = NULL;
    Node* cur = T[h(k)];
    while (cur != NULL && cur->key != k) { prev = cur; cur = cur->next; }
    if (cur == NULL) return false;
    if (prev == NULL) T[h(k)] = cur->next;
    else prev->next = cur->next;
    delete cur;
    stored--;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> m >> n;
    T = new Node*[m];
    for (int i = 0; i < m; i++) T[i] = NULL;
    for (int t = 0; t < n; t++) {
        int k;
        cin >> k;
        chainInsert(k);
    }
    cin >> q;
    while (q--) {
        char op;
        int k;
        cin >> op >> k;
        if (op == 'S') cout << (chainSearch(k) != NULL ? "FOUND" : "NOT FOUND") << "\n";
        else cout << (chainDelete(k) ? "DELETED" : "NOT FOUND") << "\n";
    }
    int best = 0, bestLen = 0;
    for (int i = 0; i < m; i++) {
        int len = 0;
        cout << i << ":";
        for (Node* p = T[i]; p != NULL; p = p->next) { cout << " " << p->key; len++; }
        cout << "\n";
        if (len > bestLen) { bestLen = len; best = i; }   // strict: smallest slot wins ties
    }
    cout << fixed << setprecision(2) << "Load factor: " << (double)stored / m << "\n";
    cout << "Longest chain: slot " << best << ", length " << bestLen << "\n";
    return 0;
}
