// Brute force for 05: count 0s and 1s of every subarray, O(n^2).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int best = 0;
    for (int l = 0; l < n; l++) {
        int zeros = 0, ones = 0;
        for (int r = l; r < n; r++) {
            if (a[r] == 1) ones++; else zeros++;
            if (zeros == ones && r - l + 1 > best) best = r - l + 1;
        }
    }
    cout << best << "\n";
    return 0;
}
