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

ll n;
vector<ll> arr;
ll bad_arr_at_x(int x) {
    vector<ll> geX(n);
    for (int i = 0; i < n; i++) geX[i] = (arr[i] >= x ? 1 : -1);
    vector<ll> pfs(n);
    pfs[0] = geX[0];
    for (int i = 1; i < n; i++) pfs[i] = pfs[i - 1] + geX[i];

    ll ans = 0;
    int prevIdx = n;

    unordered_map<ll, ll> mp;
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] == x) {
            while (prevIdx > i){
                prevIdx--;
                mp[pfs[prevIdx]]++;
            }
        }

        ll p = (i > 0 ? pfs[i-1] : 0);
        ans += mp[p];
    }
    return ans;
}
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        arr.resize(n);
        for (int i = 0; i < n; i++) cin >> arr[i];

        ll ans = 0;
        for (int x = 1; x <= 10; x++) {
            ans += bad_arr_at_x(x);
        }

        ll total = n + ((n-1)*n)/2LL;
        cout << total - ans << endl;
    }
    return 0;
}