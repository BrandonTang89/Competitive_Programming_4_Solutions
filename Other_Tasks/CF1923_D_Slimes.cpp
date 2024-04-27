#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
vector<ll> presum, myarr;
vector<int> pright;

ll qsum(int l, int r)
{
    if (r < l || l < 0 || r > n - 1) return -10;
    // return sum of a[l..r]
    return presum[r] - (l > 0 ? presum[l - 1] : 0);
}

vector<int> f(vector<ll> arr)
{
    presum.assign(n, 0);
    for (int i = 0; i < n; i++) {
        presum[i] = arr[i] + (i > 0 ? presum[i - 1] : 0LL);
    }

    pright.assign(n, 0);
    int idx = 0;
    int cur = arr[0];
    int toFill = 0;
    while (toFill < n) {
        while (arr[idx] == cur && idx < n) {
            idx++;
        }

        if (idx < n) cur = arr[idx];
        while (toFill < idx) {
            pright[toFill] = idx;
            toFill++;
        }
    }

    vector<int> ans(n, -1);
    for (int i = 0; i < n; i++) {
        // determine the smallest j such that qsum(i+1, j) > arr[i]
        int l = i + 1, r = n - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (qsum(i + 1, mid) > arr[i]) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }

        if (l == i+1 && l < n && qsum(i+1, l) > arr[i]){
            ans[i] = 1;
            continue;
        }
        if (i + 1 < n && pright[i + 1] < n) {
            int res = max(l - i, pright[i + 1] - i);

            if (qsum(i + 1, l) > arr[i]) {
                ans[i] = res;
            }
        }
    }

    return ans;
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        myarr.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> myarr[i];
        }

        vector<int> ans = f(myarr);
        vector<ll> reversed = myarr;
        reverse(reversed.begin(), reversed.end());
        vector<int> ans2 = f(reversed);

        for (int i = 0; i < n; i++) {
            if (ans[i] == -1 && ans2[n - i - 1] == -1) {
                cout << "-1 ";
            }
            else if (ans[i] == -1) {
                cout << ans2[n - i - 1] << " ";
            }
            else if (ans2[n - i - 1] == -1) {
                cout << ans[i] << " ";
            }
            else {
                cout << min(ans[i], ans2[n - i - 1]) << " ";
            }
        }

        cout << "\n";
    }

    return 0;
}