// Brute force for 13: count each element by rescanning the array, O(n^2).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int uniq = -1, rep = -1;
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < n; j++) if (a[j] == a[i]) c++;
        if (c == 1 && uniq == -1) uniq = i;
        if (c > 1 && rep == -1) rep = i;
    }
    if (uniq < 0) cout << "NONE\n"; else cout << a[uniq] << "\n";
    if (rep < 0) cout << "NONE\n"; else cout << a[rep] << "\n";
    return 0;
}
