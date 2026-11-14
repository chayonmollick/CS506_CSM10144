// 10. (a) total quantity per farmer, (b) farmer-IDs in more than n/k records: hash-count version
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    long long k;
    cin >> n >> k;
    unordered_map<long long, long long> total;   // farmer-ID -> total quantity
    unordered_map<long long, long long> freq;    // farmer-ID -> number of records
    vector<long long> order;                     // IDs in order of first appearance
    for (int i = 0; i < n; i++) {
        long long id, qty;
        cin >> id >> qty;
        if (freq.find(id) == freq.end()) order.push_back(id);
        total[id] += qty;
        freq[id]++;
    }
    // (a)
    cout << order.size() << "\n";
    for (size_t i = 0; i < order.size(); i++) cout << order[i] << " " << total[order[i]] << "\n";
    // (b) "more than n/k" without division: freq * k > n
    vector<long long> heavy;
    for (size_t i = 0; i < order.size(); i++)
        if (freq[order[i]] * k > n) heavy.push_back(order[i]);
    sort(heavy.begin(), heavy.end());
    if (heavy.empty()) cout << "NONE";
    for (size_t i = 0; i < heavy.size(); i++) cout << (i ? " " : "") << heavy[i];
    cout << "\n";
    return 0;
}
