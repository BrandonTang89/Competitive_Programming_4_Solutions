/**Kattis - bundles
 * Kinda weird, I don't see how this is a DP question, maybe my solution is unintended.
 *
 * Firstly if we have equal bundles, we just save the cheaper one. Now all remaining bundles are
 * unique. Observe that given 2 bundles, they are either disjoint or a (proper) subset of each
 * other. This results in the bundles forming a tree structure where each bundle B is either made
 * out a complete set of children bundles or an incomplete set of children bundles (that do not
 * completely cover B).
 *
 * If we want to form the contents of a bundle, we either take the bundle, or we build each of the
 * children. We can do this recursively. We can make a dummy bundle that contains all items to start
 * from.
 *
 * The real question is how to determine which are the children of a bundle. We don't want to pick
 * the grandchildren by accident. The trick is to sort the bundles in descending order of number of
 * items and process the bundles in decreasing number of items. Observe that if a bundle U is a
 * child of bundle B, it has to have less items than B. If it is a grandchild (or further down), as
 * we process the bundles in decreasing order of number of elements, we will have selected the
 * parent of U to be the child of B earlier!
 *
 * We represent a bundle as a pair of long longs which represent the bitmasks of the items in the
 * bundle. To check if a bundle is a subset of another, we just check if the bitmasks are a subset
 * of each other (easy). If a bundle has an incomplete set of children, we leave it as having no
 * children.
 *
 * Time: O(m * (n + m)), Space: O(m)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int> &v) const
    {
        std::size_t seed = 0;
        seed ^= v.first + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= v.second + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

int n, m;  // num items, num_bundles
unordered_map<pair<ll, ll>, int, pair_hash> memo;
vector<tuple<ll, ll, int>> bundles;
vector<vector<int>> adjlist;

// Returns the minimum cost to buy all items in bundles[u]
// No need for DP since the problems are not overlapping (tree structure)
int rec(int u)
{
    if (adjlist[u].size() == 0) return get<2>(bundles[u]);
    int ans = 0;
    for (int v : adjlist[u]) {
        ans += rec(v);
    }
    ans = min(ans, get<2>(bundles[u]));
    return ans;
}

// Sort bundles by number of items, descending (most items first)
bool comp_bundle(tuple<ll, ll, int> &a, tuple<ll, ll, int> &b)
{
    ll bm1a = get<0>(a);
    ll bm2a = get<1>(a);
    ll bm1b = get<0>(b);
    ll bm2b = get<1>(b);

    return (__builtin_popcountll(bm1a) + __builtin_popcountll(bm2a)) >
           (__builtin_popcountll(bm1b) + __builtin_popcountll(bm2b));
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> m;
        memo.clear();
        bundles.clear();

        for (int i = 0; i < m; i++) {
            int c, a;
            cin >> c >> a;
            ll bm1 = 0;
            ll bm2 = 0;

            for (int j = 0; j < a; j++) {
                int t;
                cin >> t;
                t--;
                if (t < 64)
                    bm2 |= (1LL << t);
                else
                    bm1 |= (1LL << (t - 64));
            }

            if (memo.find({bm1, bm2}) == memo.end() || memo[{bm1, bm2}] > c) {
                memo[{bm1, bm2}] = c;
            }
        }

        ll completebm1 = 0;
        ll completebm2 = 0;
        for (int i = 0; i < n; i++) {
            if (i < 64)
                completebm2 |= (1LL << i);
            else
                completebm1 |= (1LL << (i - 64));
        }

        if (memo.find({completebm1, completebm2}) == memo.end()) {
            memo[{completebm1, completebm2}] = 1e9;
        }

        for (auto &[bm, c] : memo) {
            ll bm1 = bm.first;
            ll bm2 = bm.second;
            bundles.emplace_back(bm1, bm2, c);
        }

        sort(bundles.begin(), bundles.end(), comp_bundle);

        m = bundles.size();
        adjlist.assign(m, vector<int>());
        for (int i = 0; i < m; i++) {
            ll bm1 = get<0>(bundles[i]);
            ll bm2 = get<1>(bundles[i]);

            vector<int> children;
            for (int j = i + 1; j < m; j++) {
                auto &[bm1j, bm2j, c] = bundles[j];
                if ((bm1j & bm1) == bm1j && (bm2j & bm2) == bm2j) {
                    children.push_back(j);
                    bm1 &= ~bm1j;
                    bm2 &= ~bm2j;
                }
            }
            if (bm1 == 0 && bm2 == 0) {
                adjlist[i] = children;
            }
        }
        int ans = rec(0);  // the full bundle is definitely at bundle[0]
        assert(ans != 1e9);
        cout << ans << endl;
    }

    return 0;
}