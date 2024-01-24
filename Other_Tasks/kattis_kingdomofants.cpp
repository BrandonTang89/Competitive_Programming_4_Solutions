/**Kattis - kingdomofants
 * Segment Tree Modification. While I had to read the editorial for the idea, the implementation was
 * also quite cool. The idea is to do a line sweep from left to right and keep track of the number
 * of rectangles overlapping each cell along the y axis. We do this using a RURQ segment tree.
 * Crucially, we need to be able to add a positive or negative amount to a range, and do range even
 * (how many entries are even) and range zero (how many entries are zero) queries. We also should
 * use lazy node creation to save memory.
 *
 * Supporting numEven is quite easy. The idea is that upon an addition on a range, we can just
 * invert the number of even numbers if the addition is odd, else we keep it the same.
 *
 * The issue is numZeros. Which sounds hard to do, but if we go for numMin queries (number of
 * minimums in a range), we actually realise that we have done numZero since we will always have at
 * least 1 zero in range range (the top element of the y-axis which is never covered). numMin is
 * also somewhat straightforward to keep track of.
 *
 * This is achieved by modifying a library all-in-one segment tree.
 *
 * Time: O(n log n), Space: O(n log n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct node {
    int s, e;
    ll mn, mx, sum, add_val, set_val;
    ll numMin, numEven;
    bool lset;
    node *l, *r;
    node(int _s, int _e, int A[] = NULL)
        : s(_s),
          e(_e),
          mn(0),
          mx(0),
          sum(0),
          lset(0),
          add_val(0),
          set_val(0),
          l(NULL),
          r(NULL),
          numMin(_e - _s + 1),
          numEven(_e - _s + 1)
    {
        if (A == NULL) return;
        if (s == e) {
            mn = mx = sum = A[s];
            numMin = 1;
            numEven = (A[s] % 2 == 0) ? 1 : 0;
        }
        else {
            l = new node(s, (s + e) >> 1, A), r = new node((s + e + 2) >> 1, e, A);
            combine();
        }
    }
    void create_children()
    {
        if (s == e) return;
        if (l != NULL) return;
        int m = (s + e) >> 1;
        l = new node(s, m);
        r = new node(m + 1, e);
    }
    void self_set(ll v)
    {
        lset = 1;
        mn = mx = set_val = v;
        sum = v * (e - s + 1);
        add_val = 0;
        numEven = (v % 2 == 0) ? (e - s + 1) : 0;
        numMin = (e - s + 1);  // all are min
    }
    void self_add(ll v)
    {
        if (lset) {
            self_set(v + set_val);
            return;
        }
        mn += v, mx += v, add_val += v;
        sum += v * (e - s + 1);
        if (!(v%2 == 0)) numEven = (e - s + 1 - numEven);  // invert numEven
        // numMin is unchanged
    }
    void lazy_propagate()
    {
        if (s == e) return;
        if (lset) {
            l->self_set(set_val), r->self_set(set_val);
            lset = set_val = 0;
        }
        if (add_val != 0) {
            l->self_add(add_val), r->self_add(add_val);
            add_val = 0;
        }
    }
    void combine()
    {
        if (l == NULL) return;

        if (l->mn == r->mn) {
            numMin = l->numMin + r->numMin;
        }
        else if (l->mn > r->mn)
            numMin = r->numMin;
        else
            numMin = l->numMin;

        sum = l->sum + r->sum;
        mn = min(l->mn, r->mn);
        mx = max(l->mx, r->mx);
        numEven = l->numEven + r->numEven;
    }
#define UPDATE(name)                             \
    void name(int x, int y, ll v)                \
    {                                            \
        if (s == x && e == y) {                  \
            self_##name(v);                      \
            return;                              \
        }                                        \
        int m = (s + e) >> 1;                    \
        create_children();                       \
        lazy_propagate();                        \
        if (x <= m) l->name(x, min(y, m), v);    \
        if (y > m) r->name(max(x, m + 1), y, v); \
        combine();                               \
    }
    UPDATE(add)  // generates add
    UPDATE(set)  // generates set
#define QUERY(name, fn, var, lazyfn)                                 \
    ll range_##name(int x, int y)                                    \
    {                                                                \
        if (s == x && e == y) return var;                            \
        if (l == NULL || lset) return lazyfn(var);                   \
        int m = (s + e) >> 1;                                        \
        lazy_propagate();                                            \
        if (y <= m) return l->range_##name(x, y);                    \
        if (x > m) return r->range_##name(x, y);                     \
        return fn(l->range_##name(x, m), r->range_##name(m + 1, y)); \
    }
#define SAME(var) (var)
#define PART(var) ((var) / (e - s + 1) * (y - x + 1))
#define SUM(a, b) ((a) + (b))
    QUERY(min, min, mn, SAME)   // generates range_min
    QUERY(max, max, mx, SAME)   // generates range_max
    QUERY(sum, SUM, sum, PART)  // generates range_sum
    QUERY(nummin, SUM, numMin, PART);
    QUERY(even, SUM, numEven, PART);

    ~node()
    {
        if (l != NULL) delete l;
        if (r != NULL) delete r;
    }
} *root;

int main()
{
    node *root = new node(-1e9, 1e9);
    vector<tuple<ll, ll, ll, ll>> events;  // (x coord, bottom y, top y, increment)

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        events.emplace_back(x1, (ll)y1, (ll)y2 - 1, 1);
        events.emplace_back(x2, (ll)y1, (ll)y2 - 1, -1);
    }

    sort(events.begin(), events.end());

    ll positiveEven = 0;
    ll lastX = -1e9;

    int idx = 0;
    while (idx < events.size()) {
        // query first
        auto [x, y1, y2, inc] = events[idx];
        positiveEven += (x - lastX) * (root->range_even(-1e9, 1e9) - root->range_nummin(-1e9, 1e9));

        // // update
        root->add(y1, y2, inc);
        idx++;
        while (idx < events.size() && get<0>(events[idx]) == x) {
            auto [x, y1, y2, inc] = events[idx];
            root->add(y1, y2, inc);
            idx++;
        }

        lastX = x;
    }
    assert(root->range_sum(-1e9, 1e9) == 0);

    cout << positiveEven << endl;
    return 0;
}