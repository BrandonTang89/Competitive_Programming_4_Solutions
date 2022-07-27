/**Kattis - sylvester
 * Observe that given the binary representation of the x and y coordinates of the cell, we can determine
 * the value by counting the number of binary places such that both the digits for x and y are 1, this
 * is the number of inversions of the cell.
 * 
 * Time: O(hw), Space: O(1)
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

int num_tc;
int main() {
    fast_cin();
    cin >> num_tc;
    while (num_tc--) {
        ll n, x, y, w, h;
        cin >> n >> x >> y >> w >> h;

        for (int yi = y; yi < y + h; yi++) {
            for (int xi = x; xi < x + w; xi++) {
                cout << (__builtin_popcountll(xi & yi) % 2 == 0 ? 1 : -1) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}