/**Kattis - wipeyourwhiteboards
 * We use extended euclid's algorithm to determine the bezout's coefficients and find a initial
 * solution for r * a + s * b == q. Next is to manipulate a and b such that they are both positive.
 * There can be some funky math, but just brute force will adding or subtracting a -= s / gcd;
 * b += r / gcd; is good enough. Ensure we move both low enough (at least 1 <= 0) before moving up.
 *
 * Time: O(? not 100% sure), Mem: O(1)
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

ll extEuclid(ll a, ll b, ll &x, ll &y)
{  // pass x and y by ref
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {  // repeats until b == 0
        ll q = a / b;
        tie(a, b) = tuple(b, a % b);
        tie(x, xx) = tuple(xx, x - q * xx);
        tie(y, yy) = tuple(yy, y - q * yy);
    }
    return a;  // returns gcd(a, b)
               // ax + by = gcd(a, b)
}
int main()
{
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        ll r, s, q;
        cin >> r >> s >> q;
        s = -s;

        ll x, y;
        ll gcd = extEuclid(r, s, x, y);
        ll k = q / gcd;
        ll a = k * x;
        ll b = k * y;
        s = -s;
        b = -b;

        while (b > 0 && a > 0) {
            a += s;
            b -= r;
        }
        while (b <= 0 || a <= 0) {
            a -= s / gcd;
            b += r / gcd;
        }
        assert(r * a + s * b == q);
        assert(a >= 1 && b >= 1);
        cout << a << " " << b << endl;
    }

    return 0;
}