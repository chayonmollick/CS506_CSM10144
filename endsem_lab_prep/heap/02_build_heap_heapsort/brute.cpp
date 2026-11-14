// Brute: line 1 = BUILD-MAX-HEAP written literally (recursive); line 2 = std::sort.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<long long> A; int hs;
void heapify(int i) {
    int l = 2 * i, r = 2 * i + 1, g = i;
    if (l <= hs && A[l] > A[g]) g = l;
    if (r <= hs && A[r] > A[g]) g = r;
    if (g != i) { swap(A[i], A[g]); heapify(g); }
}
int main() {
    int n; cin >> n; A.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> A[i];
    hs = n;
    for (int i = n / 2; i >= 1; i--) heapify(i);
    cout << "Max-heap:"; for (int i = 1; i <= n; i++) cout << " " << A[i]; cout << "\n";
    sort(A.begin() + 1, A.end());
    cout << "Sorted:"; for (int i = 1; i <= n; i++) cout << " " << A[i]; cout << "\n";
    return 0;
}
