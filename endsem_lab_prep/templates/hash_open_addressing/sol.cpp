// Template: open addressing (linear / quadratic / double hashing) with DELETED tombstones.
// Input : m
//         LINEAR | QUADRATIC c1 c2 | DOUBLE
//         q, then q lines, each one of   I x | S x | D x | P
// Probe i (i = 0, 1, ..., m-1), with h'(k) = k mod m:
//   LINEAR    h(k,i) = (h'(k) + i) mod m
//   QUADRATIC h(k,i) = (h'(k) + c1*i + c2*i*i) mod m
//   DOUBLE    h(k,i) = (h'(k) + i*h2(k)) mod m,  h2(k) = 1 + (k mod (m-1))
// Output: I -> "slot j probes p" | DUPLICATE | OVERFLOW
//         S -> "FOUND j probes p" | "NOT FOUND probes p"
//         D -> "DELETED j" | NOT FOUND
//         P -> the m slots on one line: key, '-' = empty (NIL), 'D' = tombstone
#include <climits>
#include <iostream>
#include <string>
using namespace std;

const int NIL = INT_MIN;          // never used: keys are in [-1e9, 1e9]
const int DEL = INT_MIN + 1;      // tombstone: "a key was here, keep probing"
enum Method { LINEAR, QUADRATIC, DOUBLE };

struct OpenTable {
    int m;
    Method type;
    long long c1, c2;   // quadratic constants
    int* T;             // T[j] = key, NIL or DEL
};

long long md(long long a, long long b) { return ((a % b) + b) % b; }  // mod that is >= 0

void initTable(OpenTable& H, int m, Method type, long long c1, long long c2) {
    H.m = m; H.type = type; H.c1 = c1; H.c2 = c2;
    H.T = new int[m];
    for (int j = 0; j < m; j++) H.T[j] = NIL;
}

// h(k, i): slot examined by the i-th probe for key k
int probe(const OpenTable& H, long long k, long long i) {
    long long h1 = md(k, H.m);
    if (H.type == LINEAR) return (int)md(h1 + i, H.m);
    if (H.type == QUADRATIC) return (int)md(h1 + H.c1 * i + H.c2 * i * i, H.m);
    long long h2 = (H.m > 1) ? 1 + md(k, H.m - 1) : 1;
    return (int)md(h1 + i * h2, H.m);
}

// HASH-SEARCH: skip tombstones, stop at the key, at NIL, or after m probes
int hashSearch(const OpenTable& H, int k, int& probes) {
    for (int i = 0; i < H.m; i++) {
        int j = probe(H, k, i);
        probes = i + 1;
        if (H.T[j] == k) return j;
        if (H.T[j] == NIL) return -1;
    }
    return -1;
}

// HASH-INSERT: first slot that is NIL or DEL (a tombstone can be reused); -1 = overflow
int hashInsert(OpenTable& H, int k, int& probes) {
    for (int i = 0; i < H.m; i++) {
        int j = probe(H, k, i);
        probes = i + 1;
        if (H.T[j] == NIL || H.T[j] == DEL) { H.T[j] = k; return j; }
    }
    probes = H.m;
    return -1;
}

// HASH-DELETE: find the key, then leave a tombstone (writing NIL would cut probe paths)
int hashDelete(OpenTable& H, int k) {
    int p;
    int j = hashSearch(H, k, p);
    if (j != -1) H.T[j] = DEL;
    return j;
}

void printTable(const OpenTable& H) {
    for (int j = 0; j < H.m; j++) {
        if (j) cout << " ";
        if (H.T[j] == NIL) cout << "-";
        else if (H.T[j] == DEL) cout << "D";
        else cout << H.T[j];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int m, q;
    string w;
    long long c1 = 0, c2 = 0;
    cin >> m >> w;
    Method type = LINEAR;
    if (w == "QUADRATIC") { type = QUADRATIC; cin >> c1 >> c2; }
    else if (w == "DOUBLE") type = DOUBLE;
    OpenTable H;
    initTable(H, m, type, c1, c2);
    cin >> q;
    while (q--) {
        char op;
        cin >> op;
        if (op == 'P') { printTable(H); continue; }
        int x, p = 0;
        cin >> x;
        if (op == 'I') {
            if (hashSearch(H, x, p) != -1) { cout << "DUPLICATE\n"; continue; }  // keys stay distinct
            int j = hashInsert(H, x, p);
            if (j == -1) cout << "OVERFLOW\n";
            else cout << "slot " << j << " probes " << p << "\n";
        } else if (op == 'S') {
            int j = hashSearch(H, x, p);
            if (j == -1) cout << "NOT FOUND probes " << p << "\n";
            else cout << "FOUND " << j << " probes " << p << "\n";
        } else if (op == 'D') {
            int j = hashDelete(H, x);
            if (j == -1) cout << "NOT FOUND\n";
            else cout << "DELETED " << j << "\n";
        }
    }
    delete[] H.T;
    return 0;
}
