/**Kattis - logland
 * Some thinking is required to get the solution. Essentially the greedy comes from taking all of
 * the largest denomination if possible, else discarding it then repeating. A naive implementation
 * would take O(n^2) as for each denomination it takes O(n) to check if we can take all. However. we
 * can improve this by pre-processing the initial array by consolidating smaller denominations to
 * form the largest possible denominations (done in the aug vector). Note the invariant that
 * aug[largest_denom] >= v[largest_denom] since aug[largest_denom] is augmented by the smaller
 * denominations compiled. If aug[largest_denom] > v[largest_denom] or v[largest_denom] is even, we
 * can take all of the largest denom. Else, we need to lose one copy of the largest_denom. We can
 * then modify the aug in O(1) to process the second largest denom and so on. Refer to the code
 * below.
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

ll MOD = 1e9 + 7;
inline ll mod(ll a, ll b) { return (a % b + b) % b; }

// O(log p) exponentiation with modulus
ll fexp(ll b, ll p, ll m = MOD) {
    if (p == 0) return 1;

    ll ans = fexp(b, p >> 1, m);
    ans = mod(ans * ans, m);
    if (p & 1) ans = mod(ans * b, m);
    return ans;
}

int n;
vector<int> v, aug;
int main() {
    fast_cin();
    cin >> n;
    v.resize(n);
    aug.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        aug[i] += v[i];
        if (i != n - 1) {
            aug[i + 1] = aug[i] / 2;
            aug[i] %= 2;
        }
    }
    ll ans = 0;
    ll cur_pow = fexp(2, n - 1);
    for (int i = n - 1; i > 0; i--) {
        if (v[i] % 2 == 0 || (v[i] < aug[i])) {
            aug[i] -= v[i];
            aug[i - 1] += 2 * aug[i];
        } else {
            // we need lose one copy of this one
            aug[i] -= v[i];
            ans += cur_pow;
            ans %= MOD;
        }
        cur_pow *= 500000004;  // mod inverse of 2, mod 1e9+7
        cur_pow %= MOD;
    }

    ans += (aug[0] % 2);
    ans %= MOD;
    cout << ans << endl;

    return 0;
}