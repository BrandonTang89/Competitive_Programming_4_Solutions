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

int n, m;
vector<string> a;
vector<vector<string>> b;
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> m;
        a.resize(n);
        b.assign(m, vector<string>(n));
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                cin >> b[j][i];
            }
        }

        // check that for each i, there is a j such that a[i] = b[j][i]
        // if not, return -1
        bool all_there = true;
        for (int i = 0; i < n; i++) {
            bool found = false;
            for (int j = 0; j < m; j++) {
                if (a[i] == b[j][i]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                all_there = false;
                break;
            }
        }
        if (!all_there) {
            cout << -1 << endl;
            continue;
        }

        // find the j with the most common elements with a[i]
        int max_count = 0;
        int max_j = -1;
        for (int j = 0; j < m; j++) {
            int count = 0;
            for (int i = 0; i < n; i++) {
                if (a[i] == b[j][i]) {
                    count++;
                }
            }
            if (count > max_count) {
                max_count = count;
                max_j = j;
            }
        }

        int manually_fill = n - max_count;
        cout << n + 2 * manually_fill << endl;
    }

    return 0;
}