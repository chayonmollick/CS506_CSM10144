// 05. Longest subarray with equal 0s and 1s using a hand-written chained hash map
#include <iostream>
using namespace std;

struct Node {
    int key;       // prefix sum
    int idx;       // first index where this prefix sum occurred
    Node* next;
};

const int M = 100003;
Node* T[M];        // global: all NULL

int h(int k) { return ((k % M) + M) % M; }   // prefix sums can be negative

Node* findNode(int k) {
    for (Node* p = T[h(k)]; p != NULL; p = p->next)
        if (p->key == k) return p;
    return NULL;
}

void insertKey(int k, int idx) {             // head insertion; caller checks absence
    Node* x = new Node;
    x->key = k; x->idx = idx; x->next = T[h(k)];
    T[h(k)] = x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    insertKey(0, -1);
    int s = 0, best = 0;
    for (int j = 0; j < n; j++) {
        int x;
        cin >> x;
        s += (x == 1) ? 1 : -1;
        Node* p = findNode(s);
        if (p != NULL) { if (j - p->idx > best) best = j - p->idx; }
        else insertKey(s, j);
    }
    cout << best << "\n";
    return 0;
}
