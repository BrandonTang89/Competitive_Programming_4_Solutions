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

inline int inversions(int a, int b, int c, int d) {
    int ans = 0;
    if (a > b) ans++;
    if (a > c) ans++;
    if (a > d) ans++;
    if (b > c) ans++;
    if (b > d) ans++;
    if (c > d) ans++;
    return ans;
}

bool comp(const pair<int, int> &a, const pair<int, int> &b) {
    int ia = inversions(a.first, a.second, b.first, b.second);
    int ib = inversions(b.first, b.second, a.first, a.second);
    if (ia < ib) return true;
    if (ia > ib) return false;
    if (min(a.first, a.second) < min(b.first, b.second)) return true;
    if (min(a.first, a.second) > min(b.first, b.second)) return false;
    if (max(a.first, a.second) < max(b.first, b.second)) return true;
    if (max(a.first, a.second) > max(b.first, b.second)) return false;

    return false;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i].first >> arr[i].second;
        }
        stable_sort(arr.begin(), arr.end(), comp);

        for (int i = 0; i < n; i++) {
            cout << arr[i].first << " " << arr[i].second << " ";
        }
        cout << endl;
    }

    return 0;
}