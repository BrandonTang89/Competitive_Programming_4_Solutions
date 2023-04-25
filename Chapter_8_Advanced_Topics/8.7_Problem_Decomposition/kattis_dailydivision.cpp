/**Kattis - dailydivision
 * Fenwick Tree + Ternary Search. Observe that at each stage we are trying to minimise the function
 * f(x) = ||sum(arr[0..x) - sum(arr[x+1..n))| - arr[x]%2| which is convex so we can do a ternary
 * search. We can make each call of f(x) to be O(log n) by storing arr as a fenwick tree. This also
 * makes updates O(log n). Getting the ternary search to work is a bit non-trivial (tricky).
 *
 * Time: O(nq log(n)^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))  // the key operation

typedef long long ll;  // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

class FenwickTree {  // index 0 is not used
   private:
    vll ft;  // internal FT is an array
   public:
    FenwickTree(int m) { ft.assign(m + 1, 0); }  // create an empty FT

    void build(const vll &f)
    {
        int m = (int)f.size() - 1;  // note f[0] is always 0
        ft.assign(m + 1, 0);
        for (int i = 1; i <= m; ++i) {      // O(m)
            ft[i] += f[i];                  // add this value
            if (i + LSOne(i) <= m)          // i has parent
                ft[i + LSOne(i)] += ft[i];  // add to that parent
        }
    }

    FenwickTree(const vll &f) { build(f); }  // create FT based on f

    FenwickTree(int m, const vi &s)
    {  // create FT based on s
        vll f(m + 1, 0);
        for (int i = 0; i < (int)s.size(); ++i)  // do the conversion first
            ++f[s[i]];                           // in O(n)
        build(f);                                // in O(m)
    }

    ll rsq(int j)
    {  // returns RSQ(1, j)
        ll sum = 0;
        for (; j; j -= LSOne(j)) sum += ft[j];
        return sum;
    }

    ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); }  // inc/exclusion

    // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
    void update(int i, ll v)
    {
        for (; i < (int)ft.size(); i += LSOne(i)) ft[i] += v;
    }
};
FenwickTree ft(1e5); // max n

int n, q;
ll inline f(int loc)
{
    return abs(abs(ft.rsq(loc - 1) - ft.rsq(loc + 1, n)) - (ft.rsq(loc, loc) % 2LL));
}
int main()
{
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        ft.update(i, x);
    }
    for (int i = 0; i < q; i++) {
        int c, x;
        cin >> c >> x;
        c++;                             // 1 indexed
        ft.update(c, x - ft.rsq(c, c));  // hut c change to x

        int l = 1, r = n;
        while (l + 2 < r) {
            int m1 = l + (r - l) / 3;
            int m2 = l + 2 * (r - l) / 3;

            if (f(m1) <= f(m2))
                r = m2;
            else
                l = m1 + 1;
        }
        assert(l <= r);
        ll mini = INT_MAX;
        int best = -1;
        for (int i = l; i <= r; i++) {
            if (f(i) < mini) {
                mini = f(i);
                best = i;
            }
        }
        cout << best - 1 << endl;
    }
    return 0;
}