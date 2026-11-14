// Brute force for 35: try every choice (nobody or one of P players) for every position: (P+1)^N
#include <iostream>
#include <vector>
using namespace std;

int N, P, X;
vector<vector<long long> > c, v;
long long best = 0;

void go(int i, long long spent, long long value) {
    if (spent > X) return;
    if (i == N) { if (value > best) best = value; return; }
    go(i + 1, spent, value);                                     // position i empty
    for (int j = 0; j < P; j++) go(i + 1, spent + c[i][j], value + v[i][j]);
}

int main() {
    cin >> N >> P >> X;
    c.assign(N, vector<long long>(P));
    v.assign(N, vector<long long>(P));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < P; j++) cin >> c[i][j] >> v[i][j];
    go(0, 0, 0);
    cout << best << "\n";
    return 0;
}
