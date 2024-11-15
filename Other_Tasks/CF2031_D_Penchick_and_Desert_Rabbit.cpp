/**CF2031D
 * Observe that the connected components are in contiguous ranges (simple case analysis: suppose we can go from i -> j for i < j, then we can go to anything between i and j).
 * Consider going through the array from the left to right. We figure out how big the leftmost connected component is. To do so, we repeatedly expand it to the right as long as
 * the maximum of the connected component is bigger than some element on the right. For the sake of simplicity, we pick the minimum element on the right to expand to. When we can
 * no longer expand, that is the largest connected component. We can then recurse to the subproblem of dealing with the next connected component starting immdiately after the
 * current connected component. Observe that we can do up to O(n) expansions in total since each expansion increses the size of some connected component by at least 1 and the
 * sum of connected component sizes is n. We can use either a sparse table or segment tree for finding the index of the minimum element of a range, I just chose a segment tree
 * because I had the code for it but a sparse table is more efficient.
 *
 * Time complexity: O(n log n) for each test case
 * Space complexity: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

typedef long long ll;
struct Node {
    int s, e;
    ll mn, mx, sum, add_val, set_val;
    ll mn_idx, mx_idx;  // left most index of minimum and maximum
    ll num_mn, num_mx;  // number of minimums and maximums
    bool lset;
    Node *l, *r;
    Node(int _s, int _e, int A[] = NULL) : s(_s), e(_e), mn(0), mx(0), sum(0), mn_idx(_s), mx_idx(_s), num_mn(_e - _s + 1), num_mx(_e - _s + 1), lset(0), add_val(0), set_val(0), l(NULL), r(NULL) {
        if (A == NULL) return;
        if (s == e) {
            mn = mx = sum = A[s];
        } else {
            l = new Node(s, (s + e) >> 1, A), r = new Node((s + e + 2) >> 1, e, A);
            combine();
        }
    }
    void create_children() {
        if (s == e) return;
        if (l != NULL) return;
        int m = (s + e) >> 1;
        l = new Node(s, m);
        r = new Node(m + 1, e);
    }
    void self_set(ll v) {
        lset = 1;
        mn = mx = set_val = v;
        mn_idx = mx_idx = s;          // left most index
        num_mn = num_mx = e - s + 1;  // all are the same
        sum = v * (e - s + 1);
        add_val = 0;
    }
    void self_add(ll v) {
        if (lset) {
            self_set(v + set_val);
            return;
        }
        mn += v, mx += v, add_val += v;
        sum += v * (e - s + 1);
    }
    void lazy_propagate() {
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
    void combine() {
        if (l == NULL) return;
        sum = l->sum + r->sum;
        mn = min(l->mn, r->mn);
        mx = max(l->mx, r->mx);
        mn_idx = l->mn <= r->mn ? l->mn_idx : r->mn_idx;
        mx_idx = l->mx >= r->mx ? l->mx_idx : r->mx_idx;
        num_mn = (l->mn == mn ? l->num_mn : 0) + (r->mn == mn ? r->num_mn : 0);
        num_mx = (l->mx == mx ? l->num_mx : 0) + (r->mx == mx ? r->num_mx : 0);
    }

#define UPDATE(name)                             \
    void name(int x, int y, ll v) {              \
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

#define QUERY(name, fn, var, lazyfn)                                   \
    ll range_##name(int x, int y) {                                    \
        if (s == x && e == y) return var;                              \
        /* optimise for when all the elements in the range are equal*/ \
        if (l == NULL || lset) return lazyfn(var);                     \
        int m = (s + e) >> 1;                                          \
        lazy_propagate();                                              \
        if (y <= m) return l->range_##name(x, y);                      \
        if (x > m) return r->range_##name(x, y);                       \
        return fn(l->range_##name(x, m), r->range_##name(m + 1, y));   \
    }

#define SAME(var) (var)
#define PART(var) ((var) / (e - s + 1) * (y - x + 1))
#define SUM(a, b) ((a) + (b))
    QUERY(min, min, mn, SAME)          // generates range_min
    QUERY(max, max, mx, SAME)          // generates range_max
    QUERY(sum, SUM, sum, PART)         // generates range_sum
    QUERY(num_min, SUM, num_mn, PART)  // generates range_num_min
    QUERY(num_max, SUM, num_mx, PART)  // generates range_num_max

    pair<ll, ll> get_min_with_idx(pair<ll, ll> a, pair<ll, ll> b) {
        if (a.first < b.first) return a;
        if (a.first > b.first) return b;
        return a.second < b.second ? a : b;  // right most index
    }
    pair<ll, ll> range_min_with_idx(int x, int y) {  // returns (mn, idx)
        if (s == x && e == y) return {mn, mn_idx};
        if (l == NULL || lset) return {mn, mn_idx};
        int m = (s + e) >> 1;
        lazy_propagate();
        if (y <= m) return l->range_min_with_idx(x, y);
        if (x > m) return r->range_min_with_idx(x, y);
        return get_min_with_idx(l->range_min_with_idx(x, m), r->range_min_with_idx(m + 1, y));
    }

    pair<ll, ll> get_max_with_idx(pair<ll, ll> a, pair<ll, ll> b) {
        if (a.first > b.first) return a;
        if (a.first < b.first) return b;
        return a.second > b.second ? a : b;  // right most index
    }
    pair<ll, ll> range_max_with_idx(int x, int y) {  // returns (mx, idx)
        if (s == x && e == y) return {mx, mx_idx};
        if (l == NULL || lset) return {mx, mx_idx};
        int m = (s + e) >> 1;
        lazy_propagate();
        if (y <= m) return l->range_max_with_idx(x, y);
        if (x > m) return r->range_max_with_idx(x, y);
        return get_max_with_idx(l->range_max_with_idx(x, m), r->range_max_with_idx(m + 1, y));
    }

    ~Node() {
        if (l != NULL) delete l;
        if (r != NULL) delete r;
    }
};

int main() {
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        Node *seg = new Node(0, n - 1, a.data());

        vector<int> ans(n, -1);  // the component it is in
        for (int left = 0; left < n;) {
            int right = left;
            int maxi = a[left];
            while (right < n - 1) {
                auto [mn, mn_idx] = seg->range_min_with_idx(right + 1, n - 1);
                if (mn >= maxi) break;
                right = mn_idx;
                maxi = seg->range_max(left, right);
            }

            for (int j = left; j <= right; j++) {
                ans[j] = maxi;
            }

            left = right + 1;
        }

        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;

        delete seg;
    }

    return 0;
}