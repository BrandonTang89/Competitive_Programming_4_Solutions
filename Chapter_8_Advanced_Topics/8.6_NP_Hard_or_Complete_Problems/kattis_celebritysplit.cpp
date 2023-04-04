/**Kattis - celebritysplit
 * Bruteforce/DP + Meet in the middle.
 *
 * From the front, we let dp(diff, i) be the minimum cost assuming that the current (positive
 * difference since the sign actually doesn't matter) between the 2 people is diff and that the next
 * property to consider is i. We can either add v[i] or subtract v[i] from diff, or pay for the cost
 * of selling the property. Since the state space is very large, this is approximately O(3^n) which
 * will TLE.
 *
 * What we notice is that we need to reach 0 diff at the end, so we can do a meet in the middle,
 * going from the back and finding the minimum cost to reach 0 diff from any (diff, i). We just
 * implement this as a 3^n brute force recursion.
 *
 * Now, we meet at n/2 and the time taken is O(3^(n/2) * 2) which is AC. There are other minor
 * optimisations made (like exiting when diff is too big even if we subtract the rest of the v[i]s)
 * in dp but they are probably not very relevant.
 * 
 * Time: O(3^(n/2) * 2), Mem: O(3^(n/2))
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int>& v) const
    {
        std::size_t seed = 0;
        seed ^= v.first + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= v.second + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};
int n;
vector<ll> v, pfs;  // pfs is prefix sum
unordered_map<pair<ll, int>, ll, pair_hash> memo;
unordered_map<ll, ll> middle;
ll total;
ll dp(ll diff, int i)
{
    if (i == n / 2) {
        if (middle.find(diff) != middle.end()) {
            return middle[diff];
        }
        return 1e16;
    }
    if (memo.find({diff, i}) != memo.end()) {
        return memo[{diff, i}];
    }
    if (i > 0 && total - pfs[i - 1] < diff) {
        return memo[{diff, i}] = 1e16;
    }

    ll ans = 1e16;
    ans = min(ans, dp(abs(diff - v[i]), i + 1));
    if (ans > 0) ans = min(ans, dp(diff + v[i], i + 1));
    if (ans > v[i]) ans = min(ans, v[i] + dp(diff, i + 1));
    return memo[{diff, i}] = ans;
}

void back_to_mid(ll diff, int i, ll cost)  // from (diff, i) we get to 0 diff at the end with cost
{
    if (i == n / 2) {
        if (middle.find(diff) == middle.end()) {
            middle[diff] = cost;
        }
        else {
            middle[diff] = min(middle[diff], cost);
        }
    }
    else {
        back_to_mid(abs(diff - v[i - 1]), i - 1, cost);
        back_to_mid(diff + v[i - 1], i - 1, cost);
        back_to_mid(diff, i - 1, cost + v[i - 1]);
    }
}
int main()
{
    while (1) {
        cin >> n;
        if (n == 0) {
            break;
        }
        v.resize(n);
        pfs.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            total += v[i];
        }
        sort(v.begin(), v.end(), greater<ll>());
        for (int i = 0; i < n; i++) {
            pfs[i] = v[i];
            if (i > 0) {
                pfs[i] += pfs[i - 1];
            }
        }
        memo.clear();
        middle.clear();
        back_to_mid(0, n, 0);
        cout << dp(0, 0) << endl;
    }

    return 0;
}