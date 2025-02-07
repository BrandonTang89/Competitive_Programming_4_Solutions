// The main difficulty is in doing everything with the numbers multiplied by 2 to avoid having to deal with floating point numbers...
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
int main(){
    int tc;
    cin >> tc;
    while (tc--){
        ll n, k, l;
        cin >> n >> k >> l;

        vector<ll> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
            a[i] *= 2;
        }
        l *= 2;
        k *= 2;

        if (l == 0) {
            cout << 0 << endl;
            continue;
        }

        ll ans = a[0]; // two times the amount of time passed
        ll pos = k; // two times the position of the crow

        for (int i=1; i<n; i++){
            if (pos >= l) break;
            if (a[i] <= pos){
                ll x =  min(pos, a[i] + ans);
                pos = x + k;
            }
            else{
                if (a[i] - pos <= ans){
                    pos = pos + k;
                }
                else{
                    ll y = a[i] - ans;
                    assert( y % 2 == pos % 2);
                    ll moveBy = (y - pos) / 2;
                    ans += moveBy;
                    pos = (y - moveBy) + k;

                }
            }
        }

        if (pos < l){
            ans += l-pos;
        }

        cout << ans << endl;
    }

    return 0;
}