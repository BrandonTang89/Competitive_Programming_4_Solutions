/**Vjudge - UVA - 1674
 * https://vjudge.net/problem/UVA-1674
 * Lightning Energy Report. Heavy light decomposition + fenwick tree.
 * 
 * Time: O(q (log n)^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
#define LSOne(S) (S & (-S))
#define MAXN 51000

int n, q, num_child[MAXN], par[MAXN], seg[MAXN], segroot[MAXN], segdepth[MAXN], height[MAXN],
    segitempos[MAXN], segcount;
vector<int> adjlist[MAXN];
vector<int> segitem[MAXN];
int count_child(int x, int p) {
    par[x] = p;
    num_child[x] = 1;
    for (vector<int>::iterator it = adjlist[x].begin(); it != adjlist[x].end(); ++it) {
        if (*it == p) continue;
        num_child[x] += count_child(*it, x);
    }
    return num_child[x];
}
void decomp(int x, int s, int sd, int h) {
    seg[x] = s;
    height[x] = h;
    segdepth[x] = sd;
    segitempos[x] = segitem[s].size();
    segitem[s].push_back(x);
    int largest = -1;
    for (vector<int>::iterator it = adjlist[x].begin(); it != adjlist[x].end(); ++it) {
        if (*it == par[x]) continue;
        if (largest == -1) largest = *it;
        if (num_child[largest] < num_child[*it]) largest = *it;
    }
    if (largest == -1) return;
    decomp(largest, s, sd, h + 1);
    for (vector<int>::iterator it = adjlist[x].begin(); it != adjlist[x].end(); ++it) {
        if (*it == largest) continue;
        if (*it == par[x]) continue;
        segroot[++segcount] = x;
        decomp(*it, segcount, sd + 1, h + 1);
    }
}
int lca(int a, int b) {
    if (a == b) return a;
    if (seg[a] == seg[b]) {
        if (height[a] < height[b])
            return a;
        else
            return b;
    }
    if (segdepth[a] > segdepth[b])
        return lca(segroot[seg[a]], b);
    else if (segdepth[a] < segdepth[b])
        return lca(a, segroot[seg[b]]);
    else
        return lca(segroot[seg[a]], segroot[seg[b]]);
}

class FenwickTree {  // index 0 is not used
   private:
    vll ft;  // internal FT is an array
   public:
    FenwickTree(int m) { ft.assign(m + 1, 0); }  // create an empty FT

    void build(const vll &f) {
        int m = (int)f.size() - 1;  // note f[0] is always 0
        ft.assign(m + 1, 0);
        for (int i = 1; i <= m; ++i) {      // O(m)
            ft[i] += f[i];                  // add this value
            if (i + LSOne(i) <= m)          // i has parent
                ft[i + LSOne(i)] += ft[i];  // add to that parent
        }
    }

    FenwickTree(const vll &f) { build(f); }  // create FT based on f

    FenwickTree(int m, const vi &s) {  // create FT based on s
        vll f(m + 1, 0);
        for (int i = 0; i < (int)s.size(); ++i)  // do the conversion first
            ++f[s[i]];                           // in O(n)
        build(f);                                // in O(m)
    }

    ll rsq(int j) {  // returns RSQ(1, j)
        ll sum = 0;
        for (; j; j -= LSOne(j)) sum += ft[j];
        return sum;
    }

    ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); }  // inc/exclusion

    // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
    void update(int i, ll v) {
        for (; i < (int)ft.size(); i += LSOne(i)) ft[i] += v;
    }

    int select(ll k) {  // O(log m)
        int p = 1;
        while (p * 2 < (int)ft.size()) p *= 2;
        int i = 0;
        while (p) {
            if (k > ft[i + p]) {
                k -= ft[i + p];
                i += p;
            }
            p /= 2;
        }
        return i + 1;
    }
};
class RUPQ {  // RUPQ variant
   private:
    FenwickTree ft;  // internally use PURQ FT
   public:
    RUPQ(int m) : ft(FenwickTree(m)) {}
    void range_update(int ui, int uj, ll v) {
        ft.update(ui, v);                        // [ui, ui+1, .., m] +v
        ft.update(uj + 1, -v);                   // [uj+1, uj+2, .., m] -v
    }                                            // [ui, ui+1, .., uj] +v
    ll point_query(int i) { return ft.rsq(i); }  // rsq(i) is sufficient
};
vector<RUPQ> fenwick_trees;  // Remember that these are 1-indexed

void update_upwards(int u, int dest, ll amt) {
    if (seg[u] == seg[dest]) {
        fenwick_trees[seg[u]].range_update(segitempos[dest] + 1, segitempos[u] + 1, amt);
        return;
    }
    fenwick_trees[seg[u]].range_update(1, segitempos[u] + 1, amt);
    update_upwards(segroot[seg[u]], dest, amt);  // jump up the chain
}
void path_update(int u, int v, int w) { // increments all vertices along path from u to v by w
    int ancestor = lca(u, v);
    update_upwards(u, ancestor, w);
    update_upwards(v, ancestor, w);
    update_upwards(ancestor, ancestor, -w);
}

ll node_query(int u){
    return fenwick_trees[seg[u]].point_query(segitempos[u] + 1);
}
int main() {
    int num_tc;
    cin >> num_tc;
    for (int tc = 0; tc < num_tc; tc++) {
        cout << "Case #" << tc + 1 << ":" << endl;
        cin >> n;
        for (int i = 0; i < n; i++) {
            adjlist[i].clear();
            segitem[i].clear();
        }
        segcount = 0;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }
        count_child(0, -1);
        decomp(0, segcount, 0, 0);

        fenwick_trees.clear();
        for (int i = 0; i < segcount + 1; i++) {
            fenwick_trees.emplace_back(RUPQ(segitem[i].size()));
        }
        // node u is in the segment seg[u] with index segitempos[u]
        int q;
        cin >> q;
        for (int i = 0; i < q; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            path_update(u, v, w);
        }

        for (int i = 0; i < n; i++) {
            cout << node_query(i) << endl;
        }
    }
    return 0;
}