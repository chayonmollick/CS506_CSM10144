// 28. Consecutive Subsequence (CF 977F): longest subsequence x, x+1, ..., x+k-1; print k and its indices
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // len[v] = length of the longest valid subsequence (seen so far) that ends with value v
    unordered_map<int, int> len;
    int best = 0, endVal = 0;
    for (int i = 0; i < n; i++) {
        unordered_map<int, int>::iterator it = len.find(a[i] - 1);
        int prev = (it == len.end()) ? 0 : it->second;   // base case: no value a[i]-1 yet -> 0
        len[a[i]] = prev + 1;                            // extend the chain ending at a[i]-1
        if (len[a[i]] > best) {                          // strictly greater -> earliest end wins ties
            best = len[a[i]];
            endVal = a[i];
        }
    }

    // reconstruction: values endVal-best+1 .. endVal, pick the leftmost index for each in turn
    cout << best << "\n";
    int want = endVal - best + 1, printed = 0;
    for (int i = 0; i < n && printed < best; i++) {
        if (a[i] == want) {
            cout << (printed ? " " : "") << i + 1;
            printed++;
            want++;
        }
    }
    cout << "\n";
    return 0;
}
