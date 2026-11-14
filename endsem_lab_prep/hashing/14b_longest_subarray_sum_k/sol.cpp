// 14b. Longest subarray with sum exactly K (K = 0: largest zero-sum subarray)
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    long long K;
    cin >> n >> K;
    unordered_map<long long, int> first;      // prefix sum -> FIRST index where it occurred
    first[0] = -1;                            // empty prefix
    long long prefix = 0;
    int best = 0;
    for (int j = 0; j < n; j++) {
        long long x;
        cin >> x;
        prefix += x;
        unordered_map<long long, int>::iterator it = first.find(prefix - K);
        if (it != first.end() && j - it->second > best) best = j - it->second;  // a[i+1..j] sums to K
        if (first.find(prefix) == first.end()) first[prefix] = j;              // keep earliest only
    }
    cout << best << "\n";
    return 0;
}
