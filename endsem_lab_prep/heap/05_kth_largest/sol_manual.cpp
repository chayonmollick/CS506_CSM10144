// 05. K-th largest with a hand-written min-heap of size K (no STL containers).
#include <iostream>
using namespace std;

const int MAXN = 100005;
long long A[MAXN];          // min-heap A[1..n], n <= k
int n = 0;
long long ans[MAXN];

void swapAt(int i, int j) { long long t = A[i]; A[i] = A[j]; A[j] = t; }
void minHeapify(int i) {
    while (true) {
        int l = 2 * i, r = 2 * i + 1, s = i;
        if (l <= n && A[l] < A[s]) s = l;
        if (r <= n && A[r] < A[s]) s = r;
        if (s == i) return;
        swapAt(i, s);
        i = s;
    }
}
void insertKey(long long x) {
    A[++n] = x;
    int i = n;
    while (i > 1 && A[i / 2] > A[i]) { swapAt(i, i / 2); i /= 2; }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int total, k, cnt = 0;
    cin >> total >> k;
    for (int i = 0; i < total; i++) {
        long long x;
        cin >> x;
        if (n < k) insertKey(x);                     // heap not full yet
        else if (x > A[1]) { A[1] = x; minHeapify(1); }   // replace the smallest of the top k
        if (n == k) ans[cnt++] = A[1];
    }
    cout << A[1] << '\n';
    for (int i = 0; i < cnt; i++) cout << ans[i] << (i + 1 < cnt ? ' ' : '\n');
    return 0;
}
