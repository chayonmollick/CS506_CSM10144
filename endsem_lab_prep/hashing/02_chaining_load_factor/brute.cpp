// Brute force for 02: keep all keys in one vector in insertion order and rebuild the chains
// at the end (chain i = keys with slot i, newest first).
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int m, n, q;
    cin >> m >> n;
    vector<int> keys;   // distinct keys, oldest first
    for (int t = 0; t < n; t++) {
        int k;
        cin >> k;
        bool dup = false;
        for (size_t i = 0; i < keys.size(); i++) dup = dup || keys[i] == k;
        if (!dup) keys.push_back(k);
    }
    cin >> q;
    while (q--) {
        char op;
        int k;
        cin >> op >> k;
        int pos = -1;
        for (size_t i = 0; i < keys.size(); i++) if (keys[i] == k) pos = (int)i;
        if (pos < 0) printf("NOT FOUND\n");
        else if (op == 'S') printf("FOUND\n");
        else { keys.erase(keys.begin() + pos); printf("DELETED\n"); }
    }
    int best = 0, bestLen = -1;
    for (int s = 0; s < m; s++) {
        printf("%d:", s);
        int len = 0;
        for (int i = (int)keys.size() - 1; i >= 0; i--)
            if (((keys[i] % m) + m) % m == s) { printf(" %d", keys[i]); len++; }
        printf("\n");
        if (len > bestLen) { bestLen = len; best = s; }
    }
    printf("Load factor: %.2f\n", (double)keys.size() / m);
    printf("Longest chain: slot %d, length %d\n", best, bestLen);
    return 0;
}
