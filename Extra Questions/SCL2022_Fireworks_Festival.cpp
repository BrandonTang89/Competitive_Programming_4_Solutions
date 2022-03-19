/**Shopee Code League 2022 - Fireworks Festival
 * WARNING: NOT SUBMITTED FOR GRADING
 * 
 * I believe this code is correct, but I am not sure. We use 2 segment trees as a memory saving DP memo table,
 * allowing us to do range maximum query in O(log n).
 * 
 * Time: O(mn log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

struct node {
    int s, e;
    ll mn, mx, sum, add_val, set_val;
    bool lset;
    node *l, *r;
    node (int _s, int _e, int A[] = NULL): s(_s), e(_e), mn(0), mx(0), sum(0), lset(0), add_val(0), set_val(0), l(NULL), r(NULL) {
        if (A == NULL) return;
        if (s == e) mn = mx = sum = A[s];
        else {
            l = new node(s, (s+e)>>1, A), r = new node((s+e+2)>>1, e, A);
            combine();
        }
    }
    void create_children() {
        if (s == e) return;
        if (l != NULL) return;
        int m = (s+e)>>1;
        l = new node(s, m);
        r = new node(m+1, e);
    }
    void self_set(ll v) {
        lset = 1;
        mn = mx = set_val = v;
        sum = v * (e-s+1);
        add_val = 0;
    }
    void self_add(ll v) {
        if (lset) { self_set(v + set_val); return; }
        mn += v, mx += v, add_val += v;
        sum += v*(e-s+1);
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
    #define UPDATE(name)\
    void name(int x, int y, ll v) { \
        if (s == x && e == y) { self_##name(v); return; } \
        int m = (s+e)>>1; \
        create_children(); lazy_propagate(); \
        if (x <= m) l->name(x, min(y, m), v); \
        if (y > m) r->name(max(x, m+1), y, v); \
        combine(); \
    }
    UPDATE(add)                 //generates add
    UPDATE(set)                 //generates set
    #define QUERY(name, fn, var, lazyfn)\
    ll range_##name(int x, int y) {\
        if (s == x && e == y) return var; \
        if (l == NULL || lset) return lazyfn(var);\
        int m = (s+e)>>1; lazy_propagate(); \
        if (y <= m) return l->range_##name(x, y); \
        if (x > m) return r->range_##name(x, y); \
        return fn(l->range_##name(x, m), r->range_##name(m+1, y)) ; \
    }
    #define SAME(var) (var)
    #define PART(var) ((var) /(e-s+1) * (y-x+1)) 
    #define SUM(a, b) ((a)+(b))
    QUERY(min, min, mn, SAME)   //generates range_min
    QUERY(max, max, mx, SAME)   //generates range_max
    QUERY(sum, SUM, sum, PART)  //generates range_sum
    ~node() {
        if (l != NULL) delete l;
        if (r != NULL) delete r;
    }
} *root0, *root1;

node* previous_layer(int m){
    if (m % 2 == 0) return root0;
    else return root1;
}

node* current_layer(int m){
    if (m % 2 == 1) return root0;
    else return root1;
}

int n, m, d;
vector<int> A, B, t;
int main(){ // everything should be 0 indexed
    cin >> n >> m >> d;
    A.resize(m+1);
    B.resize(m+1);
    t.resize(m+1);

    A[0] = B[0] = 0;
    t[0] = 1;
    for (int i=1; i<=m; i++){
        cin >> A[i] >> B[i] >> t[i];
        A[i]--; 
    }

    root0 = new node(0, n-1);
    root1 = new node(0, n-1);

    for (int r=1; r<=m; r++){
        int moveable = (t[r] - t[r-1]) * d;
        
        auto prev = previous_layer(r);
        auto curr = current_layer(r);

        for (int pos=0; pos<n; pos++){
            int start = max(0, pos - moveable);
            int end = min(n-1, pos + moveable);

            curr->set(pos, pos, prev->range_max(start, end) + B[r] - abs(A[r] - pos));
        }
    }

    cout << current_layer(m)->range_max(0, n-1) << endl;

    return 0;
}