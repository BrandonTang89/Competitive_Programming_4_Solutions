/**Kattis - tractor
 * Annoying problem. Basically adhoc. We are essentially finding pairs of numbers (a, b) such that
 * a<=x and b<=y such that a^b is some power of 2 - 1. I.e. For each bit position i, we can either
 * set ai = 1 or bi = 1.
 *
 * Theres essentially 2 types of solutions, those where max(MSB(a), MSB(b)) = max(MSB(x), MSB(y)).
 * I.e. we use all the bits available. This is calculated by all_bits(x, y). The other type is where
 * we have some zero bits for both a and b at the front. This is calculated in the main function.
 *
 * all_bits basically sets a and b to follow x and y from their most significant bit until theres a
 * bit position that is both set or both unset in x and y. Then terminating (use some math to figure
 * out what the answer should be then).
 *
 * To deal with the other type, we go from the MSB to LSB and record whether we have seen a set bit
 * in x or y thus far. We use that information to figure out the number of ways to set a and b
 * assuming we start setting bits from position i-1.
 * 
 * Generally this is just tedious, try to figre out what is going on and then just code it up.
 * 
 * Time: O(log x + log y), Mem: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

inline int MSB(unsigned int x) { return 32 - __builtin_clz(x); }
int maxx, maxy;
inline ll all_bits(int x, int y)
{
    for (int i = MSB(y) - 1; i >= 0; i--) {
        if ((x & (1 << i)) && (y & (1 << i))) {
            int top = i;
            x &= ((1 << top) - 1);
            y &= ((1 << top) - 1);
            return (x + 1) + (y + 1);
        }
        if (!(x & (1 << i)) && !(y & (1 << i))) {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> maxx >> maxy;
        if (maxx > maxy) swap(maxx, maxy);

        ll ans = all_bits(maxx, maxy);

        int xdone = 0;
        int ydone = 0;
        for (int i = MSB(maxy) - 1; i > 0; i--) {
            if (xdone == 0 && (maxx & (1 << i))) {
                xdone = 1;
            }
            if (ydone == 0 && (maxy & (1 << i))) {
                ydone = 1;
            }

            if (xdone && ydone) {
                ans += (1LL << i);
            }
            else if (xdone) {
                ans += (maxy & ((1 << i) - 1)) + 1;
            }
            else if (ydone) {
                ans += (maxx & ((1 << i) - 1)) + 1;
            }
        }
        cout << ans + 1 << endl;
    }

    return 0;
}