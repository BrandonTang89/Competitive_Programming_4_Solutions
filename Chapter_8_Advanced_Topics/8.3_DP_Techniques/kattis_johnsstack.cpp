/**Kattis - johnsstack
 * I found this quite difficult.
 *
 * Firstly observe that in each move, we can either move some book in the first sorted segment or
 * the one directly below the first sorted segment to the top. Notice that it is always optimal to
 * take the one directly below the first sorted segment. This is because to take the kth book, the
 * first k-1 books must be sorted. Taking some book within the first k-1 books will waste moves
 * because we will need to return to this state again to take kth book.
 *
 * Okay but naive simulation will take way too long (roughly 2^50?). Instead, what we can see is
 * that we are kinda doing "insertion sort" from the top down, inserting the kth book into the
 * sorted stack of k-1 books repeatedly. Now, to do this insertion, we will move the kth book to the
 * top, then do this "overlapping subproblem" of inserting the to book PAST the first x books i.e.
 * it will have to be in position x after. The issue is we can't just use x as the DP state because
 * the books are not necessarily distinct.
 *
 * What we will do is observe that we will convert [a0, a1, ..., ax-1] (the first x books which are
 * sorted) into a bit mask [b0, b1, ..., bx-1] where b0 = 0, bi = 1 iff ai = ai-1. This information
 * together with x is sufficient to determine the number of moves to insert the top book past the
 * first x sorted books.
 *
 * The base cases are x = 0 and x = 1. For x >= 2, we first insert the top book past the first x-1
 * sorted books into position x-1 [0 index] (subproblem). Then we will take the largest of the
 * sorted segment (currently still at position x [0 indexed]), put it to the top (1 move). Then move
 * it down until the "right position" which is where it is > the the book before it and == all the
 * books after (excluding the book we were inserting). This is where the bit mask comes in to use to
 * find the relevant position. I.e. we remove the least significant bits of the bitmask while they
 * are 1, then remove the next 0. You probably need to draw it out to understand...
 * 
 * Time: O(? not all states are visited), Space: O(? not all states are visited)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

vector<int> v;
map<pair<ll, int>, ll> memo;

ll dp(ll bm, int l)
{
    if (memo.count({bm, l})) return memo[{bm, l}];

    if (l == 0) return 0;
    if (l == 1) return 1;

    ll ans = 1LL + dp(bm >> 1LL, l - 1);
    ll nbm = bm;
    int nl = l;
    while (nbm & 1) {
        nbm >>= 1LL;
        nl--;
    }
    nbm >>= 1LL;
    nl--;
    ans += dp(nbm, nl);
    return memo[{bm, l}] = ans;
}

ll myhash(int x)
{
    if (x == 0) return 0;
    ll bm = 0;

    for (int i = 1; i < x; i++) {
        bm <<= 1LL;
        if (v[i] == v[i - 1]) bm |= 1LL;
    }
    return bm;
}

int main()
{
    int tc;
    cin >> tc;

    while (tc--) {
        int n;

        cin >> n;
        v.resize(n);
        for (int i = 0; i < n; i++) cin >> v[i];

        ll ans = 0;

        while (true) {  // while not sorted
            int x = 1;
            while (x < n && v[x] >= v[x - 1]) {
                x++;
            }

            if (x == n) break;

            ans += 1LL;

            while (v[x] <= v[x - 1]) {
                swap(v[x], v[x - 1]);
                x--;
            }

            ll bm = myhash(x);
            ans += dp(bm, x);
        }

        cout << ans << endl;
    }

    return 0;
}