/**Kattis - arrayrepetition
 * Decently straightforward binary search question.
 *
 * I decided to keep the index as a 1-index.
 *
 * The idea is we maintain a list of the lengths of the array after each operation. We can then
 * binary search to find the largest index i such that lens[i] < k. Now, if lens[i+1] == k and
 * op[i+1] == 1, it means that we add x[i+1] to the array to get the kth element, so we just return
 * x[i+1]. Else, we know that we are at some multiple of the array after the first i operations so
 * we do a modulo to get the index of the element within that array. We will definitely be "undoing"
 * a "repeat the array" operation whenever we encouter this case. This means that remaining array
 * length must fall by at least half so this can only happen (log 1e18) times.
 * 
 * Each binary search is O(log n) and we have q queries, leading to
 * Time: O(q log n log 1e18), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int main()
{
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<ll> lens(n + 1), op(n + 1), x(n + 1);
        lens[0] = 0;
        op[0] = 0;
        x[0] = -1;
        for (int i = 1; i <= n; i++) {
            cin >> op[i] >> x[i];
            if (lens[i - 1] >= (ll)1e18) {
                lens[i] = lens[i - 1];
                continue;
            }
            if (op[i] == 1) {
                lens[i] = lens[i - 1] + 1;
            }
            else {
                __int128 temp = (__int128)lens[i - 1] * (__int128)(x[i] + 1);
                if (temp >= (ll)1e18) {
                    lens[i] = (ll)1e18;
                    continue;
                }
                lens[i] = lens[i - 1] * (x[i] + 1);
            }
        }

        while (q--) {
            ll k;
            cin >> k;
            assert(k <= lens[n]);
            while (true) {
                // get largest index i such that lens[i] < k
                ll i = lower_bound(lens.begin(), lens.end(), k) - lens.begin() - 1;
                if (lens[i + 1] == k && op[i + 1] == 1) {
                    cout << x[i + 1] << " ";
                    break;
                }
                k = k % lens[i];
                if (k == 0LL) k = lens[i];
            }
        }
        cout << "\n";
    }

    return 0;
}
