// 01. Min-heap operations by command (hand-written heap, no STL containers).
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 100005;
long long A[MAXN];   // A[1..n] is the min-heap, PARENT(i)=i/2, LEFT(i)=2i, RIGHT(i)=2i+1
int n = 0;

void swapAt(int i, int j) { long long t = A[i]; A[i] = A[j]; A[j] = t; }

void minHeapify(int i) {                     // float A[i] down
    while (true) {
        int l = 2 * i, r = 2 * i + 1, s = i;
        if (l <= n && A[l] < A[s]) s = l;
        if (r <= n && A[r] < A[s]) s = r;
        if (s == i) return;
        swapAt(i, s);
        i = s;
    }
}
void insertKey(long long x) {                // put at the end, bubble up
    A[++n] = x;
    int i = n;
    while (i > 1 && A[i / 2] > A[i]) { swapAt(i, i / 2); i /= 2; }
}
long long extractMin() {                     // caller checks n > 0
    long long m = A[1];
    A[1] = A[n--];
    minHeapify(1);
    return m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    while (q--) {
        string op;
        cin >> op;
        if (op == "insert") {
            long long x; cin >> x;
            insertKey(x);
        } else if (op == "getMin") {
            if (n == 0) cout << "EMPTY\n"; else cout << A[1] << '\n';
        } else if (op == "removeMin") {
            if (n == 0) cout << "EMPTY\n"; else cout << extractMin() << '\n';
        } else if (op == "size") {
            cout << n << '\n';
        }
    }
    if (n == 0) cout << "EMPTY\n";
    while (n > 0) {
        cout << extractMin();
        cout << (n == 0 ? '\n' : ' ');
    }
    return 0;
}
