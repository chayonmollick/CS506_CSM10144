// R1: rod cutting, max revenue + the pieces (s[j] = smallest first piece that is optimal).
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main() {
    int n;
    cin >> n;
    vector<ll> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];
    vector<ll> r(n + 1, 0);
    vector<int> s(n + 1, 0);
    for (int j = 1; j <= n; j++) {
        r[j] = -1;
        for (int i = 1; i <= j; i++)
            if (p[i] + r[j - i] > r[j]) { r[j] = p[i] + r[j - i]; s[j] = i; }   // strict >: smallest i wins
    }
    cout << r[n] << '\n';
    for (int j = n; j > 0; j -= s[j]) cout << s[j] << (j - s[j] > 0 ? ' ' : '\n');
    return 0;
}
