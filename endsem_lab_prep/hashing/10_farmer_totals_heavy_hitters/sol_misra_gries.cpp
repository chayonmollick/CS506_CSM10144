// 10. Same I/O; part (b) with Misra-Gries: two passes, only k-1 counters (O(k) memory).
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<long long> id(n), qty(n);           // stored only so we can "read the file" twice
    for (int i = 0; i < n; i++) cin >> id[i] >> qty[i];

    // (a) one pass with a hash map: farmer-ID -> total
    unordered_map<long long, long long> total;
    vector<long long> order;
    for (int i = 0; i < n; i++) {
        if (total.find(id[i]) == total.end()) order.push_back(id[i]);
        total[id[i]] += qty[i];
    }
    cout << order.size() << "\n";
    for (size_t i = 0; i < order.size(); i++) cout << order[i] << " " << total[order[i]] << "\n";

    // (b) pass 1: keep at most k-1 (candidate, counter) pairs
    vector<long long> cand(k - 1, 0);
    vector<int> cnt(k - 1, 0);                 // cnt[c] == 0 means slot c is free
    for (int i = 0; i < n; i++) {
        int hit = -1, freeSlot = -1;
        for (int c = 0; c < k - 1; c++) {
            if (cnt[c] > 0 && cand[c] == id[i]) hit = c;
            else if (cnt[c] == 0 && freeSlot == -1) freeSlot = c;
        }
        if (hit != -1) cnt[hit]++;                                    // known candidate
        else if (freeSlot != -1) { cand[freeSlot] = id[i]; cnt[freeSlot] = 1; }   // free counter
        else for (int c = 0; c < k - 1; c++) cnt[c]--;               // k distinct IDs cancel
    }
    // pass 2: exact counts of the surviving candidates
    vector<long long> heavy;
    for (int c = 0; c < k - 1; c++) {
        if (cnt[c] == 0) continue;
        long long occ = 0;
        for (int i = 0; i < n; i++) if (id[i] == cand[c]) occ++;
        if (occ * k > n) heavy.push_back(cand[c]);                   // occ > n/k
    }
    sort(heavy.begin(), heavy.end());
    if (heavy.empty()) cout << "NONE";
    for (size_t i = 0; i < heavy.size(); i++) cout << (i ? " " : "") << heavy[i];
    cout << "\n";
    return 0;
}
