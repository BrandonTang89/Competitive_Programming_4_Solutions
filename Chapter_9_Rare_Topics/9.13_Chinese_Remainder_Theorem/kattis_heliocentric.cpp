/**Kattis - heliocentric
 * Just a basic application of chinese remainder theorem. Intro question.
 * 
 * Time: O(1), Space: O(1)
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
int mod(int a, int n) { return (a % n + n) % n; }

int extEuclid(int a, int b, int &x, int &y) {  // pass x and y by ref
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {  // repeats until b == 0
        ll q = a / b;
        tie(a, b) = tuple(b, a % b);
        tie(x, xx) = tuple(xx, x - q * xx);
        tie(y, yy) = tuple(yy, y - q * yy);
    }
    return a;  // returns gcd(a, b)
}

int modInverse(int a, int n) {  // returns modular inverse of a mod n
    int x, y;
    extEuclid(a, n, x, y);
    return mod(x, n);
}
int crt(vi r, vi m) {
    // m_t = m_0*m_1*...*m_{n-1}
    int mt = accumulate(m.begin(), m.end(), 1, multiplies<>());
    int x = 0;
    for (int i = 0; i < (int)m.size(); ++i) {
        int a = mod((ll)r[i] * modInverse(mt / m[i], m[i]), m[i]);
        x = mod(x + (ll)a * (mt / m[i]), mt);
    }
    return x;
}
int e, m, case_counter = 0;
int main() {
    while (cin >> e >> m) {
        vi r = {365 - e, 687 - m};
        vi m = {365, 687};

        cout << "Case " << ++case_counter << ": " << crt(r, m) << endl;
    }

    return 0;
}