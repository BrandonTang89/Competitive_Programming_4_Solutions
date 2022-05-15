/**Kattis - programmingtutors
 * BSTA + check if theres a perfect MCBM. Pretty easy.
 * 
 * Time: O(log(1e9) * kn^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
vector<pair<int, int>> vertices;
int mandist(int u, int v) {
    return abs(vertices[u].first - vertices[v].first) +
           abs(vertices[u].second - vertices[v].second);
}

vector<int> adjlist(int u, int max_weight) {
    vector<int> ans;
    int s = (u <= n - 1) ? n : 0;
    int e = (u <= n - 1) ? n * 2 : n;
    for (int i = s; i < e; i++) {
        if (i == u) continue;
        if (mandist(u, i) <= max_weight) {
            ans.push_back(i);
        }
    }
    return ans;
};

vector<int> match, visited;
// MCBM Augmenting Path Algorithm
int aug(int L, int max_weight) {
    if (visited[L]) return 0;
    visited[L] = 1;
    for (auto R : adjlist(L, max_weight)) {
        if (match[R] == -1 || aug(match[R], max_weight)) {
            match[R] = L;
            match[L] = R;
            return 1;
        }
    }
    return 0;
}

int cal_MCBM(int max_weight) {
    match.assign(2 * n, -1);
    unordered_set<int> freeV;
    for (int L = 0; L < n; L++) freeV.emplace(L);
    int MCBM = 0;
    int Vleft = n;  // number of vertices in left partition

    for (int L = 0; L < Vleft; L++) {  // all left vectices
        vector<int> candidates;
        for (auto R : adjlist(L, max_weight)) {  // all right vectices neighbouring u
            if (match[R] == -1) {                // if v is unassigned
                candidates.push_back(R);
            }
        }
        if ((int)candidates.size() > 0) {
            MCBM++;
            freeV.erase(L);
            int a = rand() % candidates.size();
            match[candidates[a]] = L;
        }
    }

    // MCBM Calculation
    for (auto &L : freeV) {
        visited.assign(Vleft, 0);
        MCBM += aug(L, max_weight);
    }

    return MCBM;
}

int main() {
    cin >> n;
    int x, y;
    for (int i = 0; i < 2 * n; i++) {
        cin >> x >> y;
        vertices.emplace_back(x, y);
    }

    int lo = 0, hi = 1e9;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (cal_MCBM(mid) < n) {  // no perfect matching, we need to increase the max weight
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    cout << lo << endl;

    return 0;
}