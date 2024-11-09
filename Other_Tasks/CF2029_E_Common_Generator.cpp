#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

typedef long long ll;
typedef vector<ll> vll;

constexpr ll inf = 1e18;
int _sieve_size;
vector<ll> lowestpf, primes;
void smallestPF(ll upperbound = (ll)4e5 + 2) {
    _sieve_size = upperbound + 1;
    lowestpf.assign(_sieve_size, inf);

    for (ll i = 2; i < _sieve_size; i++) {
        if (lowestpf[i] == inf) {
            lowestpf[i] = i;
            for (ll j = i * i; j < _sieve_size; j += i) {
                lowestpf[j] = min(lowestpf[j], i);
            }
            primes.push_back(i);
        }
    }
}  // Time: O(n log log n)

vector<tuple<ll, ll>> prime_factorise_sieve(ll n) {
    assert(n < _sieve_size && n >= 1);
    vector<tuple<ll, ll>> prime_factors;
    while (n != 1) {
        ll p = lowestpf[n];
        ll e = 0;
        while (lowestpf[n] == p) {
            n /= p;
            e++;
        }
        prime_factors.push_back({p, e});
    }
    return prime_factors;
}  // Time: O(log n)

constexpr int top = 4e5;

int main() {
    fast_cin();
    smallestPF();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vll arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        // check if any element is a prime
        int numPrimes = 0;
        int thePrime = -1;
        for (int i = 0; i < n; i++) {
            if (lowestpf[arr[i]] == arr[i]) {
                numPrimes++;
                thePrime = arr[i];
            }
        }

        if (numPrimes == 0) {
            cout << 2 << endl;
            continue;
        }
        if (numPrimes == 1 && thePrime == 2) {
            cout << 2 << endl;
            continue;
        }
        if (numPrimes > 1) {
            cout << -1 << endl;  // impossible
            continue;
        }

        bool canDo = true;
        for (int i = 0; i < n; i++) {
            if (arr[i] == thePrime) {
                continue;
            }
            int pf = lowestpf[arr[i]];
            if (thePrime * pf  > arr[i] && (thePrime * 2  > arr[i] - pf)) {
                canDo = false;
                break;
            }
        }

        if (canDo) {
            cout << thePrime << endl;
        } else {
            cout << -1 << endl;
        }
    }

    return 0;
}