// Brute: compare every node with ALL its ancestors (definition), literal recursive BUILD-MAX-HEAP.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<long long> A; int n;
void hf(int i) {
    int l = 2 * i, r = 2 * i + 1, g = i;
    if (l <= n && A[l] > A[g]) g = l;
    if (r <= n && A[r] > A[g]) g = r;
    if (g != i) { swap(A[i], A[g]); hf(g); }
}
int main() {
    cin >> n; A.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> A[i];
    bool mx = true, mn = true;
    for (int j = 2; j <= n; j++)
        for (int a = j / 2; a >= 1; a /= 2) { if (A[a] < A[j]) mx = false; if (A[a] > A[j]) mn = false; }
    cout << "Max-heap: " << (mx ? "YES" : "NO") << "\n" << "Min-heap: " << (mn ? "YES" : "NO") << "\n";
    for (int i = n / 2; i >= 1; i--) hf(i);
    cout << "Converted:"; for (int i = 1; i <= n; i++) cout << " " << A[i]; cout << "\n";
    return 0;
}
