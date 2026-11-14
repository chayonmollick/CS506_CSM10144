// Brute: slides written literally (recursive heapify, MAX-HEAP-INSERT via -infinity).
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<long long> A(1); int hs = 0;
void hf(int i) {
    int l = 2 * i, r = 2 * i + 1, g = i;
    if (l <= hs && A[l] > A[g]) g = l;
    if (r <= hs && A[r] > A[g]) g = r;
    if (g != i) { swap(A[i], A[g]); hf(g); }
}
void inc(int i, long long k) { A[i] = k; while (i > 1 && A[i/2] < A[i]) { swap(A[i], A[i/2]); i /= 2; } }
int main() {
    int n, q; cin >> n; A.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> A[i];
    hs = n; for (int i = n / 2; i >= 1; i--) hf(i);
    cin >> q;
    while (q--) {
        string op; cin >> op;
        if (op == "maximum") { if (!hs) cout << "EMPTY\n"; else cout << A[1] << "\n"; }
        else if (op == "extractMax") { if (!hs) { cout << "EMPTY\n"; continue; }
            cout << A[1] << "\n"; A[1] = A[hs]; hs--; hf(1); }
        else if (op == "insert") { long long k; cin >> k; hs++; if ((int)A.size() <= hs) A.push_back(0);
            A[hs] = -4000000000000000000LL; inc(hs, k); }
        else if (op == "increaseKey") { int i; long long k; cin >> i >> k;
            if (i < 1 || i > hs || k < A[i]) cout << "ERROR\n"; else inc(i, k); }
        else if (op == "print") { if (!hs) cout << "EMPTY\n";
            for (int i = 1; i <= hs; i++) cout << A[i] << (i < hs ? " " : "\n"); }
    }
    return 0;
}
