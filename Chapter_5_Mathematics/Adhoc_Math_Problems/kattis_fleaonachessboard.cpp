/**Kattis - fleaonachessboard
 * Math + HashSet. We first note that a flea at (x, y) is on a white square if and only if
 *  x%2s > s && 0 < y%2s < s || 0 < x%2s < s && y%2s > s
 *
 * This means that we don't actually need to care about the absolute value of x and y, but just
 * their values modulo 2s. Since we are operating the finite field (ZZ_2s)^2, we will only have 4s^2
 * possible states. If we ever reach the same state again, we will go around in a cycle and never
 * escape. Thus, we can use a hashset to store the states we have visited and check if we have
 * visited the same state before.
 *
 * If we find a valid state, we just return the number of steps we have taken and the real final
 * position.
 * 
 * Time: O(s^2), Mem: O(s^2)
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

int main()
{
    fast_cin();
    while (true) {
        ll s, x, y, a, b;
        ll xo, yo;
        cin >> s >> xo >> yo >> a >> b;
        if (s == 0) {
            break;
        }
        x = xo % (s << 1LL);
        y = yo % (s << 1LL);
        unordered_set<ll> visited;

        int ans = 0;
        while (true) {
            if (x > s && 0 < y && y < s || 0 < x && x < s && y > s) {
                break;
            }
            visited.insert(x * (s << 1LL) + y);

            x = (x + a) % (2 * s);
            y = (y + b) % (2 * s);
            ans++;

            if (visited.find(x * (s << 1LL) + y) != visited.end()) {
                ans = -1;
                break;
            }
        }

        if (ans == -1) {
            cout << "The flea cannot escape from black squares." << endl;
        }
        else {
            cout << "After " << ans << " jumps the flea lands at (" << xo + ans * a << ", "
                 << yo + ans * b << ")." << endl;
        }
    }

    return 0;
}