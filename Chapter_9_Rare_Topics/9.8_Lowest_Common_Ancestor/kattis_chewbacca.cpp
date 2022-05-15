/**Kattis - chewbacca
 * A question that is easy in theory, but hard in practise. The problem is that 10^15 fits into
 * a long long but 10^3 * 10^15 barely does it, so using unsigned long long instead of long long
 * is just barely enough to AC.
 * 
 * Time: O(log(n)^2*q), Space: O(1)
 */
#include <bits/stdc++.h>  
using namespace std;

typedef unsigned long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

ll fexp(ll b, ll p){
    if (p == 0)return 1;
	
    ll ans = fexp(b, p >> 1LL);
    ans = ans * ans;
    if (p & 1LL) ans = ans * b;
    return ans;
}
ll n, k, q; // k-ary tree
ll parent(ll u){
    ll x = u / k;
    if ((u % k) == 0 || (u % k) == 1) return x;
    return x+1;
}

ll depth(ll u){
    if (u == 1) return 0;
    ll t = u*(k-1) + 1;
    for (ll d=1;;d++){
        if ((fexp(k, d+1) >= t) && (fexp(k, d) < t)) return d;
    }
    assert(false);
    return -1;
}

ll lca(ll u, ll v){
    while (depth(u) < depth(v)){
        v = parent(v);
    }
    while (depth(v) < depth(u)){
        u = parent(u);
    }
    while (u != v){
        u = parent(u);
        v = parent(v);
    }
    return u;
}
int main(){
    cin >> n >> k >> q;
    ll u, v;
    for (ll i=0; i<q; i++){
        cin >> u >> v;

        if (k != 1LL){
            cout << depth(u) + depth(v) - 2LL*depth(lca(u, v)) << endl;
        }
        else{
            cout << llabs(u - v) << endl;
        }
    }

    return 0;
}