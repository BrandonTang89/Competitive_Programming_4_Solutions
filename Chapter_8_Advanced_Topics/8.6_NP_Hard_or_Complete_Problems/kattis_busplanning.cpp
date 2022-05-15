/**Kattis - busplanning
 * Minimum clique cover with a max size of cliques. Print solution.
 * 
 * Time: O(3^n), Space: O(2^n);
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

string names[17];
map<string, int> fromname;

vector<int> adjmat;
int n, e, c, u, v;
int INF = 1e9;
// check if selected bus is a subset of each adjmat mask

int memo[1 << 17], next_clique[1 << 17], next_mask[1 << 17];
int dp(int mask) {            // all the ones in mask have yet to be assigned
    if (mask == 0) return 0;  // 0 more buses needed
    if (memo[mask] != -1) return memo[mask];

    int ans = INF;
    for (int ss = mask; ss; ss = (ss - 1) & mask) {  // iterate all subsets of the mask
        if (__builtin_popcount(ss) > c) continue;  // only count cliques smaller than or equal to c
        // verify that ss is a valid clique
        bool valid = true;
        int bm = ss;
        while (bm && valid) {
            int b = __builtin_ctz(bm);
            bm ^= (1 << b);
            valid = ((adjmat[b] & ss) == ss);
        }
        if (valid) {
            int nmask = mask ^ ss;
            if (ans > 1 + dp(nmask)) {
                ans = 1 + dp(nmask);
                next_clique[mask] = ss;
                next_mask[mask] = nmask;
            }
        }
    }
    return memo[mask] = ans;
}
vector<int> cliques;
void fill_cliques(int mask) {
    if (mask == 0) return;
    cliques.emplace_back(next_clique[mask]);
    fill_cliques(next_mask[mask]);
}

int main() {
    cin >> n >> e >> c;
    adjmat.assign(n, (1 << n) - 1);
    for (int i = 0; i < n; i++) {
        cin >> names[i];
        fromname[names[i]] = i;
    }
    for (int i = 0; i < e; i++) {
        string a, b;
        cin >> a >> b;
        adjmat[fromname[a]] &= ~(1 << fromname[b]);
        adjmat[fromname[b]] &= ~(1 << fromname[a]);
    }

    memset(memo, -1, sizeof memo);
    cout << dp((1 << n) - 1) << endl;
    fill_cliques((1 << n) - 1);
    reverse(cliques.begin(), cliques.end());

    for (auto clique : cliques) {
        int bm = clique;
        while (bm) {
            int b = __builtin_ctz(bm);
            bm ^= (1 << b);
            cout << names[b] << " ";
        }
        cout << endl;
    }

    return 0;
}