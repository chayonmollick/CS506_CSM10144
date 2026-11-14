// 05. Longest subarray with equal numbers of 0s and 1s (0 -> -1, then longest zero-sum subarray)
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    unordered_map<int, int> first;     // prefix sum -> FIRST index where it occurred
    first[0] = -1;                     // empty prefix sits "before" index 0
    int s = 0, best = 0;
    for (int j = 0; j < n; j++) {
        int x;
        cin >> x;
        s += (x == 1) ? 1 : -1;
        unordered_map<int, int>::iterator it = first.find(s);
        if (it != first.end()) {
            if (j - it->second > best) best = j - it->second;   // equal prefix => sum 0 in between
        } else {
            first[s] = j;              // never overwrite: earliest index gives the longest span
        }
    }
    cout << best << "\n";
    return 0;
}
