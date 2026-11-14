// 04. Count subarrays with sum K using a hand-written chained hash map (no STL containers)
#include <iostream>
using namespace std;

struct Node {
    long long key;     // prefix sum
    long long cnt;     // how many prefixes had this sum
    Node* next;
};

const int M = 100003;  // prime number of slots
Node* T[M];            // global: all NULL at start

int h(long long k) { return (int)(((k % M) + M) % M); }   // prefix sums can be negative

Node* findNode(long long k) {
    for (Node* p = T[h(k)]; p != NULL; p = p->next)
        if (p->key == k) return p;
    return NULL;
}

void increment(long long k) {             // cnt[k]++, inserting k at the head if new
    Node* p = findNode(k);
    if (p != NULL) { p->cnt++; return; }
    p = new Node;
    p->key = k; p->cnt = 1; p->next = T[h(k)];
    T[h(k)] = p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    long long K;
    cin >> n >> K;
    increment(0);                          // empty prefix
    long long prefix = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        prefix += x;
        Node* p = findNode(prefix - K);
        if (p != NULL) ans += p->cnt;
        increment(prefix);
    }
    cout << ans << "\n";
    return 0;
}
