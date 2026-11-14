// 12. Number of distinct elements in every window of size k (sliding window + hash counts)
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    unordered_map<long long, int> freq;           // value -> count inside the current window
    for (int i = 0; i < n; i++) {
        freq[a[i]]++;                              // a[i] enters
        if (i >= k) {                              // a[i-k] leaves
            if (--freq[a[i - k]] == 0) freq.erase(a[i - k]);   // keep only values present
        }
        if (i >= k - 1) cout << (i == k - 1 ? "" : " ") << freq.size();
    }
    cout << "\n";
    return 0;
}
