// 06. Longest well-performing interval: more tiring days (hours > 8) than non-tiring days
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    unordered_map<int, int> first;        // prefix score -> first index where it occurred
    int s = 0, best = 0;
    for (int i = 0; i < n; i++) {
        int hrs;
        cin >> hrs;
        s += (hrs > 8) ? 1 : -1;          // tiring day +1, otherwise -1
        if (s > 0) {
            best = i + 1;                 // the whole prefix 0..i is well-performing
        } else {
            // need an earlier prefix < s; the first one equal to s-1 is the earliest such prefix
            unordered_map<int, int>::iterator it = first.find(s - 1);
            if (it != first.end() && i - it->second > best) best = i - it->second;
        }
        if (first.find(s) == first.end()) first[s] = i;
    }
    cout << best << "\n";
    return 0;
}
