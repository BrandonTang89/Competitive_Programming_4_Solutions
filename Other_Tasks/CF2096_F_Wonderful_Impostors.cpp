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

struct node {
    int s, e;
    ll mn, mx, sum, add_val, set_val;
    bool lset;
    node *l, *r;
    node(int _s, int _e, int A[] = NULL)
        : s(_s), e(_e), mn(0), mx(0), sum(0), add_val(0), set_val(0), lset(0), l(NULL), r(NULL) {
        if (A == NULL) return;
        if (s == e)
            mn = mx = sum = A[s];
        else {
            l = new node(s, (s + e) >> 1, A), r = new node((s + e + 2) >> 1, e, A);
            combine();
        }
    }
    void create_children() {
        if (s == e) return;
        if (l != NULL) return;
        int m = (s + e) >> 1;
        l = new node(s, m);
        r = new node(m + 1, e);
    }
    void self_set(ll v) {
        lset = 1;
        mn = mx = set_val = v;
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
#define QUERY(name, fn, var, lazyfn)                                 \
    ll range_##name(int x, int y) {                                  \
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
    ~node() {
        if (l != NULL) delete l;
        if (r != NULL) delete r;
    }

    ll first_idx_greater_than(int x, int y, ll v) {
        if (mx <= v) return -1;
        if (s == e) return s;
        if (l == NULL || lset) return max(x, s);  // if all the same, return the left most index

        int m = (s + e) >> 1;
        lazy_propagate();
        if (y <= m) return l->first_idx_greater_than(x, y, v);
        if (x > m) return r->first_idx_greater_than(x, y, v);

        int leftidx = l->first_idx_greater_than(x, m, v);
        if (leftidx != -1) return leftidx;  // not found in left subtree
        return r->first_idx_greater_than(m + 1, y, v);
    }

    ll first_idx_smaller_than(int x, int y, ll v) {
        if (mn >= v) return -1;
        if (s == e) return s;
        if (l == NULL || lset) return max(x, s);  // if all the same, return the left most index

        int m = (s + e) >> 1;
        lazy_propagate();
        if (y <= m) return l->first_idx_smaller_than(x, y, v);
        if (x > m) return r->first_idx_smaller_than(x, y, v);

        int leftidx = l->first_idx_smaller_than(x, m, v);
        if (leftidx != -1) return leftidx;  // not found in left subtree
        return r->first_idx_smaller_than(m + 1, y, v);
    }

    ll last_idx_smaller_than(int x, int y, ll v) {
        if (mn >= v) return -1;
        if (s == e) return s;
        if (l == NULL || lset) return min(y, e);  // if all the same, return the right most index

        int m = (s + e) >> 1;
        lazy_propagate();
        if (y <= m) return l->last_idx_smaller_than(x, y, v);
        if (x > m) return r->last_idx_smaller_than(x, y, v);

        int rightidx = r->last_idx_smaller_than(m + 1, y, v);
        if (rightidx != -1) return rightidx;  // not found in right subtree
        return l->last_idx_smaller_than(x, m, v);
    }

    ll last_idx_greater_than(int x, int y, ll v) {
        if (mx <= v) return -1;
        if (s == e) return s;
        if (l == NULL || lset) return min(y, e);  // if all the same, return the right most index

        int m = (s + e) >> 1;
        lazy_propagate();
        if (y <= m) return l->last_idx_greater_than(x, y, v);
        if (x > m) return r->last_idx_greater_than(x, y, v);

        int rightidx = r->last_idx_greater_than(m + 1, y, v);
        if (rightidx != -1) return rightidx;  // not found in right subtree
        return l->last_idx_greater_than(x, m, v);
    }
};

int n, m;
vector<int> low;  // low(r) is the lowest i such that statements[i..r] are satisfiable
vector<tuple<int, int, int>> arr;
vector<tuple<int, int, int>> b_stmts;  // {r, l, idx}
vector<int> b_stmt_idx;                // b_stmt_idx[i] is the position of stmt i in b_stmts
void solve() {
    cin >> n >> m;
    arr.resize(m);
    b_stmt_idx.assign(m, -1);
    b_stmts.clear();
    b_stmts.reserve(m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        arr[i] = {a, b, c};
        if (a == 1) {
            b_stmts.emplace_back(c, b, i);
        }
    }

    sort(b_stmts.begin(), b_stmts.end());
    for (int i = 0; i < (int)b_stmts.size(); i++) {
        auto [r, l, idx] = b_stmts[i];
        b_stmt_idx[idx] = i;
    }

    unique_ptr<node> blx(new node(0, m));
    blx->set(0, m, -1);  // all not activated initialy

    int left = 0;
    unique_ptr<node> root(new node(0, n + 1));
    low.assign(m, -1);
    // sliding window
    for (int i = 0; i < m; i++) {
        auto [op, l, r] = arr[i];
        if (op == 0) {
            root->add(l, r, 1);
            while (true) {
                int cl = root->last_idx_smaller_than(0, l, 1) + 1;
                int cr = root->first_idx_smaller_than(r, n + 1, 1) - 1;

                assert(root->range_min(cl, cr) > 0);
                assert(root->range_min(cl - 1, l) == 0);
                assert(root->range_min(r, cr + 1) == 0);

                // check if okay
                int br_idx =
                    upper_bound(b_stmts.begin(), b_stmts.end(), make_tuple(cr + 1, -1, -1)) -
                    b_stmts.begin();
                if (br_idx == 0) {
                    break;
                }
                br_idx--;

                int bl = blx->range_max(0, br_idx);

                if (bl >= cl) {  // completely covered, must remove from the left
                    auto [op2, l2, r2] = arr[left];
                    if (op2 == 0) {
                        root->add(l2, r2, -1);
                    } else {
                        blx->set(b_stmt_idx[left], b_stmt_idx[left], -1);
                    }
                    left++;
                } else {
                    break;
                }
            }

        } else {
            bool check = true;
            while (true) {
                if (check && root->range_min(l, r) == 0) break;  // avoids rechecks
                assert(left < i);
                auto [op2, l2, r2] = arr[left];
                if (op2 == 0) {
                    root->add(l2, r2, -1);
                    check = true;
                } else {
                    blx->set(b_stmt_idx[left], b_stmt_idx[left], -1);
                    check = false;
                }
                left++;
            }
            blx->set(b_stmt_idx[i], b_stmt_idx[i], l);
        }
        low[i] = left;
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (low[r] <= l) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) solve();
    return 0;
}