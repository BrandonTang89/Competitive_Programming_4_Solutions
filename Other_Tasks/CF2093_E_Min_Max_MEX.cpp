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

int n, k;
vector<int> a;

bool cando(int x) {
    // can we achieve k segments with all mex >= x?
    vector<int> achieved_by_segment(n + 2, -1);
    int idx = 0;
    for (int i = 0; i < k; i++) {
        int mex = 0;
        while (idx < n && mex < x) {
            if (achieved_by_segment[a[idx]] < i) {
                achieved_by_segment[a[idx]] = i;

                while (mex < x && achieved_by_segment[mex] == i) {
                    mex++;
                }
            }
            idx++;
        }

        if (mex < x) {
            return false;
        }
    }
    // if we reach here, we can achieve k segments with all mex >= x
    return true;
}
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> k;
        a.resize(n);
        for (auto& x : a) {
            cin >> x;
            if (x > n + 1) x = n + 1;
        }

        ll hi = 1e9;
        ll lo = 0;
        while (lo < hi) {
            int mid = (hi + lo + 1) / 2;
            if (cando(mid)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        cout << lo << "\n";
    }
    return 0;
}