// 14a. Count index pairs i < j with |a[i] - a[j]| = k (k >= 0) using hash counts
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    long long k;
    cin >> n >> k;
    unordered_map<long long, long long> cnt;      // value -> occurrences among a[0..j-1]
    long long ans = 0;
    for (int j = 0; j < n; j++) {
        long long x;
        cin >> x;
        unordered_map<long long, long long>::iterator it = cnt.find(x - k);
        if (it != cnt.end()) ans += it->second;    // earlier a[i] = x - k
        if (k != 0) {                              // k = 0: x - k and x + k are the same value
            it = cnt.find(x + k);
            if (it != cnt.end()) ans += it->second;    // earlier a[i] = x + k
        }
        cnt[x]++;
    }
    cout << ans << "\n";
    return 0;
}
