// 01. Open addressing table build, no STL containers (plain arrays, NIL sentinel).
#include <climits>
#include <cstring>
#include <iostream>
using namespace std;

const long long NIL = LLONG_MIN;   // empty slot
enum Method { LINEAR, QUADRATIC, DOUBLE };

int m;
Method type;
long long c1 = 0, c2 = 0;

long long md(long long a, long long b) { return ((a % b) + b) % b; }

int probe(long long k, long long i) {
    long long h1 = md(k, m);
    if (type == LINEAR) return (int)md(h1 + i, m);
    if (type == QUADRATIC) return (int)md(h1 + c1 * i + c2 * i * i, m);
    long long h2 = (m > 1) ? 1 + md(k, m - 1) : 1;
    return (int)md(h1 + i * h2, m);
}

// HASH-INSERT: returns the number of probes used, or -1 if no free slot in m probes
int hashInsert(long long* T, long long k) {
    for (int i = 0; i < m; i++) {
        int j = probe(k, i);
        if (T[j] == NIL) { T[j] = k; return i + 1; }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    char w[20];
    cin >> m >> w;
    type = LINEAR;
    if (strcmp(w, "QUADRATIC") == 0) { type = QUADRATIC; cin >> c1 >> c2; }
    else if (strcmp(w, "DOUBLE") == 0) type = DOUBLE;
    int n;
    cin >> n;
    long long* T = new long long[m];
    int* probes = new int[n];
    for (int j = 0; j < m; j++) T[j] = NIL;
    long long total = 0;
    for (int t = 0; t < n; t++) {
        long long k;
        cin >> k;
        probes[t] = hashInsert(T, k);
        total += (probes[t] == -1) ? m : probes[t];
    }
    cout << "Table:";
    for (int j = 0; j < m; j++) {
        if (T[j] == NIL) cout << " -";
        else cout << " " << T[j];
    }
    cout << "\nProbes:";
    for (int t = 0; t < n; t++) cout << " " << probes[t];
    cout << "\nTotal: " << total << "\n";
    delete[] T;
    delete[] probes;
    return 0;
}
