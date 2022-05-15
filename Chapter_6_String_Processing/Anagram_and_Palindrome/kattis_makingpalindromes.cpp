/**Kattis - makingpalindromes
 * Despite what CP4 says, its not too hard, don't be afraid (like i was).We use our dp function to
 * attempt to form our palindrome, starting from the left and until the middle (automatically
 * mirroring it to ensure it is a palindrome).
 *
 * We represent the state as (l, r, k) where l and r are the left and right pointer pointing to the
 * next character in s to use, from the left or right. If s[l] == s[r], we either select to use
 * s[l] (and s[r]) next, or we don't. If we use s[l], both the next char and its mirror will be used
 * as part of the subsequence. If s[l] != s[r], we either add s[l], s[r] or something different as
 * our next char. If we use s[l] or s[r], either the next char or the mirror of it will be part of
 * the subsequence respectively.
 *
 * Note to use mod frequently and use exponentiation with modulo (was stuck debugging because of
 * this).
 *
 * Time: O(n^3), Space: O(n^3)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
int n;
string s;
ll memo[209][209][209];

inline ll mod(ll a, ll b) { return (a % b + b) % b; }

// O(log p) exponentiation with modulus
ll fexp_mod(ll b, ll p, ll m) {
    if (p == 0) return 1;

    ll ans = fexp_mod(b, p >> 1, m);
    ans = mod(ans * ans, m);
    if (p & 1) ans = mod(ans * b, m);
    return ans;
}

ll dp(int l, int r, int k) {  // we are at lth char of s, rth char of s, kth char of our palindrome
    if (l > r) {
        return fexp_mod(26, k, MOD);  // any character for k more chars
    }
    if (k == 0) return 0;             // we have run out of characters to add
    if (r - l + 1 > k * 2) return 0;  // extra pruning optimisation
    if (memo[l][r][k] != -1) return memo[l][r][k];

    ll ans = 0;
    if (s[l] == s[r]) {
        ans = dp(l + 1, r - 1, k - 1) + (dp(l, r, k - 1) * 25) % MOD;
    } else {
        // take the left, take the right or something else
        ans = (dp(l + 1, r, k - 1) + dp(l, r - 1, k - 1)) % MOD + (dp(l, r, k - 1) * 24) % MOD;
    }
    // printf("%d %d %d: %lld \n", l, r, k, ans);
    return memo[l][r][k] = (ans % MOD);
}
int main() {
    memset(memo, -1, sizeof memo);
    cin >> n;
    cin >> s;

    if (n == 0)
        cout << 1 << endl;
    else {
        cout << dp(0, n - 1, n) << endl;
    }

    return 0;
}