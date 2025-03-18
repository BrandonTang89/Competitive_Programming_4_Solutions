/** CF2082 C - Math Division
 * we let dp(i) be the expected number of operations assuming we only need to deal with the prefix from the i-th least significant bit onwards, 
 * assuming that the i-th least significant bit is now 1.
 * 
 * When considering dp(i), either we do the ceil or the floor. 
 * - If we do the floor, we need to skip forward to the next 1. For all the zeros between, it doesn't matter which operation we do.
 * - If we do the ceil, we need to skip forward to the next 0, and treat if as if it is a 1. All the 1s in between will turn into 0s so the operations don't matter.
 * 
 * The base cases is when i=n-1 and i=n, which is 0 since the number will already be <= 1
 * 
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <print>

using namespace std;

typedef long long ll;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

constexpr ll MOD = 1e9 + 7;
struct mint {
    ll x;
    constexpr mint(ll xx) : x(xx) {}
    constexpr mint() : x(0) {}
    constexpr mint operator+(mint b) const { return mint((x + b.x) % MOD); }
    constexpr mint operator-(mint b) const { return mint((x - b.x + MOD) % MOD); }
    constexpr mint operator*(mint b) const { return mint((x * b.x) % MOD); }
    constexpr mint operator/(mint b) const { return *this * invert(b); }

    constexpr static ll euclid(ll a, ll b, ll &x, ll &y) {
        if (!b) return x = 1, y = 0, a;
        ll d = euclid(b, a % b, y, x);
        return y -= a / b * x, d;
    }

    constexpr static mint invert(mint a) {
        ll x, y, g = euclid(a.x, MOD, x, y);
        assert(g == 1);
        return mint((x + MOD) % MOD);
    }

    constexpr mint operator^(ll e) const {
        if (!e) return mint(1);
        mint r = *this ^ (e / 2);
        r = r * r;
        return e & 1 ? *this * r : r;
    }
};

int32_t main() {
    constexpr mint two_inv = mint::invert(2);
    constexpr int32_t MAX_N = 1e6 + 1;
    array<mint, MAX_N> memo;
    string s;

    fast_cin();

    int32_t tc;
    cin >> tc;
    while (tc--) {
        ssize_t n;
        cin >> n >> s;
        ranges::reverse(s);

        ssize_t idx = ranges::find(s, '1') - s.begin();
        memo[n] = memo[n - 1] = 0;

        int32_t current_zero = n;
        int32_t current_one = n - 1;
        for (ssize_t next_idx = n - 2; next_idx >= idx; next_idx--) {
            mint if_floor = memo[current_one] + current_one - next_idx;
            mint if_ceil = memo[current_zero] + current_zero - next_idx;
            memo[next_idx] = (if_floor + if_ceil) * two_inv;

            if (s[next_idx] == '0')
                current_zero = next_idx;
            else
                current_one = next_idx;
        }
        println("{}", (memo[idx] + idx).x);
    }

    return 0;
}