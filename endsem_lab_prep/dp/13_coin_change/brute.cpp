// Brute force for 13 (A <= 22): plain recursion, no tables.
#include <iostream>
#include <vector>
using namespace std;

int k, A;
vector<int> c;

int minCoins(int a) {                 // -1 if impossible
    if (a == 0) return 0;
    int best = -1;
    for (int i = 0; i < k; i++)
        if (c[i] <= a) {
            int r = minCoins(a - c[i]);
            if (r >= 0 && (best < 0 || r + 1 < best)) best = r + 1;
        }
    return best;
}

long long combos(int a, int from) {   // multisets: choose coins in non-decreasing index order
    if (a == 0) return 1;
    long long s = 0;
    for (int i = from; i < k; i++) if (c[i] <= a) s += combos(a - c[i], i);
    return s;
}

long long seqs(int a) {               // ordered: any coin can come first
    if (a == 0) return 1;
    long long s = 0;
    for (int i = 0; i < k; i++) if (c[i] <= a) s += seqs(a - c[i]);
    return s;
}

int main() {
    cin >> k >> A;
    c.resize(k);
    for (int i = 0; i < k; i++) cin >> c[i];
    cout << minCoins(A) << "\n" << combos(A, 0) << "\n" << seqs(A) << "\n";
    return 0;
}
