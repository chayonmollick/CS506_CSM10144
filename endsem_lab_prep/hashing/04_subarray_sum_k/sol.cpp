// 04. Count subarrays with sum exactly K (prefix sums + hash map, negatives allowed)
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    long long K;
    cin >> n >> K;
    unordered_map<long long, long long> cnt;   // prefix sum value -> how many times seen
    cnt[0] = 1;                                // empty prefix P[0] = 0
    long long prefix = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        prefix += x;
        // subarray (i0, i] has sum K  <=>  P[i0] = prefix - K
        unordered_map<long long, long long>::iterator it = cnt.find(prefix - K);
        if (it != cnt.end()) ans += it->second;
        cnt[prefix]++;                         // add AFTER the lookup
    }
    cout << ans << "\n";
    return 0;
}
