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

template <typename T = ll>
struct StaticSum {
    const int n;
    vector<T> pfs;  // arr[i] contains the range sum from 0 to i inclusively

    T rsq(int l, int r) const {              // range sum from l to r inclusively
        if (r < l) assert(false);            // invalid input
        if (l < 0 || r >= n) assert(false);  // boundary condition check
        if (l == 0) return pfs[r];
        return (pfs[r] - pfs[l - 1]);
    }

    StaticSum(const vector<T>& arr) : n(arr.size()), pfs(arr) {
        for (int i = 1; i < n; i++) {
            pfs[i] += pfs[i - 1];
        }
    }
};

int main() {
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        ll n, m, v;
        cin >> n >> m >> v;
        vector<ll> arr(n + 1);

        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        vector<ll> brr(n + 1, 0);  // brr[i] is the maximum number of animals that can be fed from arr[i] onward inclusive
        int curFood = 0;
        int curAnimals = 0;
        for (int i = n - 1; i >= 0; i--) {
            curFood += arr[i];
            if (curFood >= v) {
                curAnimals++;
                curFood = 0;
            }
            brr[i] = curAnimals;
        }

        vector<ll> crr(n + 1);  // crr[i] is the maximum number of animals that can be fed from arr[0] to arr[i] inclusive
        curFood = 0;
        curAnimals = 0;
        for (int i = 0; i < n; i++) {
            curFood += arr[i];
            if (curFood >= v) {
                curAnimals++;
                curFood = 0;
            }
            crr[i] = curAnimals;
        }

        if (crr[n - 1] < m) {  // not enough to feed m animals
            cout << -1 << endl;
            continue;
        }

        ll ans = 0;
        StaticSum<ll> ss(arr);

        int right = 0;
        int animalsFed = brr[right];
        while (animalsFed >= m) {
            right++;
            animalsFed = brr[right];
        }
        right--;
        animalsFed = brr[right];

        if (right - 1 >= 0) {
            ans = max(ans, ss.rsq(0, right - 1));  // all animals on the right of what we eat
        }
        // cout << "right: " << right << " ans: " << ans << endl;

        int left = 0;
        for (int i = 1; i < m; i++) {
            // i animals on the left, m-i animals on the right
            while (crr[left] < i) {
                left++;
            }

            while (brr[right] >= m - i) {
                right++;
            }
            right--;

            // cout << "i = " << i << " left = " << left << " right = " << right << endl;
            if (left + 1 <= right - 1) ans = max(ans, ss.rsq(left + 1, right - 1));
        }

        while (crr[left] < m) {
            left++;
        }

        // cout << "left: " << left << " ans: " << ans << endl;

        if (left + 1 <= n - 1) ans = max(ans, ss.rsq(left + 1, n - 1));  // all animals on the left

        cout << ans << endl;
    }

    return 0;
}