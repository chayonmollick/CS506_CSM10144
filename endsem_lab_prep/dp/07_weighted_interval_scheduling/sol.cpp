// 07 Weighted interval scheduling: sort by finish, p(i) by binary search,
// ITERATIVE-COMPUTE-OPT + FIND-SOLUTION
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Req {
    long long s, f, v;
    int id;  // original 1-based index
};

bool byFinish(const Req &a, const Req &b) {
    if (a.f != b.f) return a.f < b.f;
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Req> r(n + 1);  // r[1..n]
    for (int i = 1; i <= n; i++) { cin >> r[i].s >> r[i].f >> r[i].v; r[i].id = i; }
    sort(r.begin() + 1, r.end(), byFinish);

    vector<long long> fin(n + 1);
    for (int i = 1; i <= n; i++) fin[i] = r[i].f;
    // p[i] = largest j < i with f_j <= s_i (0 if none): count of finishes <= s_i among 1..i-1
    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n; i++)
        p[i] = (int)(upper_bound(fin.begin() + 1, fin.begin() + i, r[i].s) - (fin.begin() + 1));

    vector<long long> M(n + 1, 0);  // M[0] = 0 (base case)
    for (int i = 1; i <= n; i++)
        M[i] = max(M[i - 1], r[i].v + M[p[i]]);  // request i OUT / IN

    // FIND-SOLUTION: take i if v_i + M[p(i)] >= M[i-1], then jump to p(i)
    vector<int> chosen;
    int i = n;
    while (i > 0) {
        if (r[i].v + M[p[i]] >= M[i - 1]) { chosen.push_back(r[i].id); i = p[i]; }
        else i--;
    }
    sort(chosen.begin(), chosen.end());

    cout << M[n] << "\n";
    for (int k = 0; k < (int)chosen.size(); k++) cout << (k ? " " : "") << chosen[k];
    cout << "\n";
    return 0;
}
