// 11 Longest increasing subsequence in O(n log n) (tails + binary search) with reconstruction
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<long long> tails;  // tails[L-1] = smallest last value of an increasing subsequence of length L
    vector<int> tailIdx;      // tailIdx[L-1] = index in a[] of that last value
    vector<int> parent(n, -1);
    for (int i = 0; i < n; i++) {
        // first tail >= a[i] (lower_bound => strictly increasing); a[i] replaces it or extends
        int pos = lower_bound(tails.begin(), tails.end(), a[i]) - tails.begin();
        if (pos == (int)tails.size()) {
            tails.push_back(a[i]);
            tailIdx.push_back(i);
        } else {
            tails[pos] = a[i];
            tailIdx[pos] = i;
        }
        parent[i] = (pos > 0) ? tailIdx[pos - 1] : -1;  // previous element of this subsequence
    }

    int L = tails.size();
    vector<long long> lis;
    for (int i = tailIdx[L - 1]; i != -1; i = parent[i]) lis.push_back(a[i]);  // traceback
    reverse(lis.begin(), lis.end());

    cout << L << "\n";
    for (int k = 0; k < L; k++) cout << (k ? " " : "") << lis[k];
    cout << "\n";
    return 0;
}
