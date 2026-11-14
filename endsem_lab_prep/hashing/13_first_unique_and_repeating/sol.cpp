// 13. First non-repeating element and first repeating element (hash counts, two passes)
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> a(n);
    unordered_map<long long, int> cnt;               // value -> occurrences in the whole array
    for (int i = 0; i < n; i++) { cin >> a[i]; cnt[a[i]]++; }
    int uniq = -1, rep = -1;                          // indices of the answers
    for (int i = 0; i < n; i++) {                     // second pass in array order
        if (uniq == -1 && cnt[a[i]] == 1) uniq = i;
        if (rep == -1 && cnt[a[i]] > 1) rep = i;      // earliest first occurrence of a repeated value
    }
    if (uniq == -1) cout << "NONE\n"; else cout << a[uniq] << "\n";
    if (rep == -1) cout << "NONE\n"; else cout << a[rep] << "\n";
    return 0;
}
