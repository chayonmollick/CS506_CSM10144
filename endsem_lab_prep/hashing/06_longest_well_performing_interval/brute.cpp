// Brute force for 06: check every interval, O(n^2).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    int best = 0;
    for (int l = 0; l < n; l++) {
        int tiring = 0, other = 0;
        for (int r = l; r < n; r++) {
            if (h[r] > 8) tiring++; else other++;
            if (tiring > other && r - l + 1 > best) best = r - l + 1;
        }
    }
    cout << best << "\n";
    return 0;
}
