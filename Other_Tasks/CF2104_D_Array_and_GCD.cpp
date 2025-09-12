#include <numeric>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

typedef long long ll;
typedef vector<ll> vll;

ll _sieve_size;
bitset<10000010> bs;
vll primes;

// Able to handle 1e7 in < 1s
void sieve(ll upperbound = (ll)1e7) {
    _sieve_size = upperbound + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i <= _sieve_size; i++) {
        if (bs[i]) {
            for (ll j = i * i; j <= _sieve_size; j += i) {
                bs[j] = 0;
            }
            primes.push_back(i);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;
    sort(a.begin(), a.end());

    ll required = accumulate(primes.begin(), primes.begin() + n, 0LL);
    ll have = accumulate(a.begin(), a.end(), 0LL);

    for (int i = 0; i < n; i++) {
        if (have >= required) {
            cout << i << endl;
            return;
        }
        have -= a[i];
        required -= primes[n - 1 - i];
    }

    cout << n - 1 << endl;
    return;
}

int main() {
    sieve(1e7);
    int tc;
    cin >> tc;
    while (tc--) solve();

    return 0;
}