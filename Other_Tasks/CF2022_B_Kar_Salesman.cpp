#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int main() {
    fast_cin();
    int t;
    cin >> t;
    while (t--) {
        ll n, x;
        cin >> n >> x;
        vector<ll> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        sort(arr.begin(), arr.end(), greater<ll>());

        ll hi = accumulate(arr.begin(), arr.end(), 0LL);
        ll lo = hi / x;
        while (lo < hi) {
            vector<ll> h(x+2, 0);
            ll mid = lo + (hi - lo) / 2;
            h[0] = mid;
            bool valid = true;
            int pos = 0;
            for (int i = 0; i < n && valid; ++i) {
                assert(arr[i] > 0);
                ll cur = h[pos];
                ll nxt = h[pos+1];
                if (pos+1 >= x) nxt = 0;
                if (pos >= x) cur = 0;

                if (cur + nxt < arr[i]){
                    valid = false;
                    break;
                }

                ll takeFromCur = min(arr[i], cur);
                ll takeFromNxt = arr[i] - takeFromCur;
                assert(takeFromNxt <= nxt);

                h[pos+2] = h[pos+2] + takeFromNxt;
                h[pos+1] = nxt - takeFromNxt + takeFromCur;
                h[pos] = cur - takeFromCur;

                if (h[pos] == 0) pos++;
            }

            if (valid) {
                hi = mid;
            } else {
                lo = mid + 1;
            }

            
        }
        cout << lo << endl;
    }
    return 0;
}