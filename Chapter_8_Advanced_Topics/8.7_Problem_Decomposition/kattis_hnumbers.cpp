/**Kattis - hnumbers
 * Math + prefix sum. We create a modified sieve of eratosthenes to determine the prime H numbers.
 * Then we just do an O(n^2) nested 2 loops to generate all semi prime H numbers. This doesn't TLE
 * since most generated numbers will be outside the range so we can exit the inner loop early. Then
 * we store a presum of the number of semi prime H numbers up to a certain number and answer the
 * queries in O(1).
 * 
 * Time: O(1) for each query after preprocessing, Space: O(2000010)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

ll _sieve_size;
bitset<2000010> bs;
vll primes;

// Able to handle 1e7 in < 1s
void sieve(ll upperbound = (ll)2e6)
{
    _sieve_size = upperbound + 1;
    bs.set();
    bs[1] = 0;  // unit
    for (ll i = 5; i <= _sieve_size; i += 4) {
        if (bs[i]) {
            for (ll j = i * i; j <= _sieve_size; j += i * 4) {
                bs[j] = 0;
            }
            primes.push_back(i);
        }
    }
}
bitset<2000010> semiprime;
vector<int> semiprime_count(2000010);
int main()
{
    sieve();

    for (auto i : primes) {
        for (auto j : primes) {
            if (i * j > 2e6) break;
            semiprime[i * j] = 1;
        }
    }
    for (int i = 1; i <= 2e6; i++) {
        semiprime_count[i] = semiprime_count[i - 1] + semiprime[i];
    }

    while (1) {
        int q;
        cin >> q;
        if (q == 0) break;
        cout << q << " " << semiprime_count[q] << endl;
    }

    return 0;
}