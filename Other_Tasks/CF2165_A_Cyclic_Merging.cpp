#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

using ll = long long;
using vi = vector<int>;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


void solve() {
    set<pair<ll, ll>> s; // (max_value, index)
    int n;
    cin >> n;

    vector<ll> a(n);
    vector<ll> nxt(n);
    vector<ll> prv(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        nxt[i] = (i + 1) % n;
        prv[i] = (i - 1 + n) % n;
    }

    for (int i = 0; i < n; i++) {
        s.insert({max(a[i], a[nxt[i]]), i});
    }

    ll ans = 0;
    while (s.size() > 1) {
        auto [val, idx] = *s.begin();
        s.erase(s.begin());
        ans += val;

        // remove the left one
        pair<ll, ll> left_pair = {max(a[prv[idx]], a[idx]), prv[idx]};
        s.erase(left_pair);

        // now update with new pair
        nxt[prv[idx]] = nxt[idx];
        prv[nxt[idx]] = prv[idx];
        a[nxt[idx]] = val;
        pair<ll, ll> new_pair = {max(a[prv[idx]], a[nxt[idx]]), prv[idx]};
        s.insert(new_pair);        
    }

    cout << ans << '\n';
}

int main(){
    int tc; cin >> tc; while (tc--) solve();

    return 0;
}