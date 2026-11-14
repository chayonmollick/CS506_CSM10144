// Brute force for 10: for every record, rescan all records, O(n^2).
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> id(n), q(n), heavy;
    for (int i = 0; i < n; i++) cin >> id[i] >> q[i];
    int distinct = 0;
    for (int i = 0; i < n; i++) {
        bool seen = false;
        for (int j = 0; j < i; j++) seen = seen || id[j] == id[i];
        if (!seen) distinct++;
    }
    cout << distinct << "\n";
    for (int i = 0; i < n; i++) {
        bool seen = false;
        for (int j = 0; j < i; j++) seen = seen || id[j] == id[i];
        if (seen) continue;
        long long tot = 0, c = 0;
        for (int j = 0; j < n; j++) if (id[j] == id[i]) { tot += q[j]; c++; }
        cout << id[i] << " " << tot << "\n";
        if (c * k > n) heavy.push_back(id[i]);
    }
    sort(heavy.begin(), heavy.end());
    if (heavy.empty()) cout << "NONE";
    for (size_t i = 0; i < heavy.size(); i++) cout << (i ? " " : "") << heavy[i];
    cout << "\n";
    return 0;
}
