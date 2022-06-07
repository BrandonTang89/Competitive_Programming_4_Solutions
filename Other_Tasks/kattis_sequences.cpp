/**Kattis - sequences
 * 90% pen and paper to get the O(n) solution. Essentially we do a linear pass with a running sum.
 * Letting the number of 1s previously be k and the number of ?s be r, we define delta as
 * delta = (rC0)(k+0) + (rC1)(k+1) + (rC2)(k+2) + ... + (rCr)(k+r)
 * If we have a 0, we add delta to the running sum, which will effectively consider if the ?s become
 * 0 1s, 1 1s, 2 1s, etc until r 1s.
 * If we have a ?, we double the current answer and add delta. This is because there are 2 possible
 * sequences so for each of them, we have the current answer as their sums. Then we add delta
 * because one of the sequences will have a 0.
 *
 * Now, delta can be simplified to delta = k* 2^r + r* 2^(r-1) via some mathematics. We can
 * pre-compute 2^r for all needed r and thus calculate delta in O(1).
 *
 * Time: O(n), Space: O(n)
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

const ll MOD = 1e9 + 7;
vector<ll> two_pow = {1};
ll ans = 0;
string s;
int main() {
    for (int i = 0; i < 500001; i++) {
        two_pow.push_back((two_pow[i] << 1LL) % MOD);
    }

    ll k = 0, r = 0;
    cin >> s;
    for (auto c : s) {
        if (c == '1') {
            k++;
            continue;
        }
        if (c == '0') {
            ans += ((k * two_pow[r] + r * two_pow[r - 1]) % MOD);
            ans %= MOD;
            continue;
        }

        // ?
        ans *= 2;
        ans %= MOD;
        ans += ((k * two_pow[r] + r * two_pow[r - 1]) % MOD);
        ans %= MOD;
        r++;
    }
    cout << ans << endl;

    return 0;
}