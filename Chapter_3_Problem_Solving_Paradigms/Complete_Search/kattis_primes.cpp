/**Kattis - primes
 * Straightforward recursive backtracking, similar state representation to coin change with
 * unlimited number of each coin.
 * 
 * Time: O(ans), Mem: O(ans)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
vector<ll> primes, ans;
void rec(ll cur, int i, ll bound)
{
    if (i == n) {
        ans.push_back(cur);
        return;
    }
    rec(cur, i + 1, bound);
    if (cur * primes[i] <= bound) rec(cur * primes[i], i, bound);
}
int main()
{
    while (true) {
        cin >> n;
        if (n == 0) break;
        primes.resize(n);
        for (int i = 0; i < n; i++) cin >> primes[i];
        sort(primes.begin(), primes.end(), greater<ll>());
        ans.clear();

        ll x, y;
        cin >> x >> y;
        rec(1, 0, y);
        sort(ans.begin(), ans.end());
        for (int i = 0; i < (int)ans.size() - 1; i++) {
            assert(ans[i] <= y);
            if (ans[i] >= x) cout << ans[i] << ",";
        }
        if (ans.size() > 0 && ans.back() >= x) {
            cout << ans.back();
        }
        else
            cout << "none";
        cout << endl;
    }

    return 0;
}