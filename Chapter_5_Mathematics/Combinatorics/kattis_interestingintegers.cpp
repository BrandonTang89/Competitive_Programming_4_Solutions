/**Kattis - interestingintegers
 * Not 100% trivial, much math. First we observe that letting f_0 = 0, f_1 = 1, f_k = f_(k-1) + f_k,
 * we have that g_0 = a, g_k = f_(k-1) * a + f_k * b for k >= 1, where a and b are the integers we
 * are selecting.
 *
 * Now since 0 < a <= b, we have that g_k <= f_k for all k. Since n <= 1e9 < f_45, we observe that
 * we only need to try setting g_k = n for k in [2..44].
 *
 * For each k in [2..44], we are trying to find "ideal" values a and b such that n = f_(k-1) * a +
 * f_k * b. This is a linear diophantine equation, and we can use the extended euclidean algorithm
 * to start by finding s_(n-1) and t_n such that f_(n-1) * s_(n-1) + f_n * t_n = 1 = gcd(f_(n-1),
 * f_n). Note that 2 consecutive fibonacci numbers being coprime is well known.
 *
 * Now we can get that n * f_(n-1) * s_(n-1) + n * f_n * t_n = n. We can "adjust" the equation by
 * adding and subtracting multiples of the lcm(f_(n-1), f_n) as such:
 *
 * (n * s_(n-1) + xf(n)) * f_(n-1) + (n * t_n - xf_(n-1)) * f_n = n for some integer x
 *
 * Observe that here, a = n * s_(n-1) + xf(n) and b = n * t_n - xf_(n-1). Further observe that
 * "ideal" selections of b and a are such that b <= a and b is as close to a as possible (|b-a| is
 * minimized).
 *
 * Solving the inequality b <= a yields that x <= n * (s_(n-1) - t_n) / (f_(n-1) + f_n).
 * and in particular, setting x = floor(n * (s_(n-1) - t_n) / (f_(n-1) + f_n)) is optimal.
 *
 * Once we find x, we can solve for a and b. We then take the best pair (a, b) from all the k's.
 * 
 * Time: O(~1), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// ax + by = gcd(a, b)
int extEuclid(ll a, ll b, ll &x, ll &y)
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
}

ll F[45], S[45], T[45];
// F[n-1] * S[n-1] + F[n] * T[n] = 1
int main()
{
    memset(S, -1, sizeof S);
    memset(T, -1, sizeof T);
    F[0] = 0;
    F[1] = 1;
    for (int i = 2; i < 45; i++) {
        F[i] = F[i - 1] + F[i - 2];
        assert(extEuclid(F[i - 1], F[i], S[i - 1], T[i]) == 1);
    }

    int tc;
    cin >> tc;
    while (tc--) {
        ll bestb = 1e9, besta = 1e9;
        int g;
        cin >> g;
        for (int i = 2; i < 45; i++) {
            double x = g * (T[i] - S[i - 1]) / (double)(F[i - 1] + F[i]);
            ll ix = (ll)floor(x);

            ll a = g * S[i - 1] + ix * F[i];  // should guarantee that a <= b
            ll b = g * T[i] - ix * F[i - 1];

            // there may be floating point errors... heres a quick and dirty fix
            while (a > b) {
                a -= F[i];
                b += F[i - 1];
            }
            if (a <= 0) continue;

            if (b < bestb) {
                bestb = b;
                besta = a;
            }
            else if (b == bestb) {
                besta = min(besta, a);
            }
        }
        cout << besta << " " << bestb << endl;
    }

    return 0;
}