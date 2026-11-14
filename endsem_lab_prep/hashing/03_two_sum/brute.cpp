// Brute force for 03: try every pair, j outer so the smallest j wins, then the smallest i.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long target;
    cin >> target;
    for (int j = 0; j < n; j++)
        for (int i = 0; i < j; i++)
            if (a[i] + a[j] == target) { cout << i << " " << j << "\n"; return 0; }
    cout << "-1 -1\n";
    return 0;
}
