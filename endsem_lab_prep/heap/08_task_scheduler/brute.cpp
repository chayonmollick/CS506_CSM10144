// Brute: closed-form answer max(N, (maxCount - 1) * (n + 1) + #tasks with maxCount).
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int N, n; cin >> N >> n; int cnt[26] = {0};
    for (int i = 0; i < N; i++) { char c; cin >> c; cnt[c - 'A']++; }
    int mx = *max_element(cnt, cnt + 26), numMax = 0;
    for (int i = 0; i < 26; i++) if (cnt[i] == mx) numMax++;
    long long ans = max((long long)N, (long long)(mx - 1) * (n + 1) + numMax);
    cout << ans << "\n";
    return 0;
}
