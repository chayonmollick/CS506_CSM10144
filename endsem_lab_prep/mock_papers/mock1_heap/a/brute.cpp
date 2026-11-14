// Brute force for Mock 1 (a): recursive CLRS MIN-HEAPIFY (independent of sol.cpp), k smallest by sorting.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> A; int n;
void heapify(int i) {
    int l = 2 * i, r = 2 * i + 1, s = i;
    if (l <= n && A[l] < A[s]) s = l;
    if (r <= n && A[r] < A[s]) s = r;
    if (s != i) { swap(A[i], A[s]); heapify(s); }
}
int main() {
    cin >> n; A.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = n / 2; i >= 1; i--) heapify(i);
    for (int i = 1; i <= n; i++) cout << A[i] << (i == n ? '\n' : ' ');
    int k; cin >> k;
    vector<int> s(A.begin() + 1, A.end()); sort(s.begin(), s.end());
    for (int i = 0; i < k; i++) cout << s[i] << (i == k - 1 ? '\n' : ' ');
}
