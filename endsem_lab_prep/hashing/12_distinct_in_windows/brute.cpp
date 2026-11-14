// Brute force for 12: for each window, count values not seen earlier in that window. O(n k^2).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int s = 0; s + k <= n; s++) {
        int d = 0;
        for (int i = s; i < s + k; i++) {
            bool seen = false;
            for (int j = s; j < i; j++) seen = seen || a[j] == a[i];
            if (!seen) d++;
        }
        cout << (s ? " " : "") << d;
    }
    cout << "\n";
    return 0;
}
