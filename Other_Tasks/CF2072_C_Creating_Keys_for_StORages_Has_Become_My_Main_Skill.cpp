#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n, x;
        cin >> n >> x;

        vector<int> ans;
        int i = 0;
        int orSoFar = 0;
        for (; i < n - 1; i++) {
            if ((i & x) == i) {
                orSoFar |= i;
                ans.push_back(i);
            } else {
                break;
            }
        }

        if (i == n - 1 && (i | orSoFar) == x) {
            ans.push_back(i);
        } else {
            for (; i < n; i++) {
                ans.push_back(x);
            }
        }

        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}