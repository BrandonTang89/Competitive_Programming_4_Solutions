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

ll n, k;
vector<ll> arr;
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> k;
        arr.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        if (n == 1){
            cout << arr[0] + k << endl;
            continue;
        }

        sort(arr.begin(), arr.end());

        ll stopindex = -1;
        ll cursum = 0;
        for (int i = 0; i < n - 1; i++) {
            cursum += arr[i];
            if ((cursum + k) / (i + 1) < arr[i + 1]) {
                stopindex = i;
                break;
            }
        }

        // cout << "stopindex: " << stopindex << endl;
        if (stopindex == -1) {
            stopindex = n - 1;
            cursum += arr[n - 1];
        }

        ll stoppedHeights = (cursum + k) / (stopindex + 1);
        ll spent = stoppedHeights * (stopindex + 1) - cursum;
        ll remaining = k - spent;

        ll extra = n - (stopindex + 1) + remaining;
        assert(extra >= 0);

        ll mainpart = (stoppedHeights-1) * (n) + 1LL;

        // cout << "stoppedHeights: " << stoppedHeights << endl;
        // cout << "spent: " << spent << endl;
        // cout << "remaining: " << remaining << endl;
        cout << mainpart + extra << endl;
    }

    return 0;
}