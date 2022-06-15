/**Kattis - loowater
 * A classic greedy question, essentially we use the shortest height knight that can get rid of the
 * smallest dragon, then repeat.
 * 
 * Time: O(n log n + m log m), Space: O(n + m)
 */
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
    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        vector<int> D, H;  // dragon diameter, knight height
        D.resize(n);
        H.resize(m);
        for (int i = 0; i < n; i++) {
            cin >> D[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> H[i];
        }
        sort(D.begin(), D.end());
        sort(H.begin(), H.end());
        int gold = 0, d = 0, k = 0;
        while (d < n && k < m) {
            while (k < m && (D[d] > H[k])) {
                k++;
            }
            if (k == m) {
                break;
            }
            gold += H[k];
            k++;
            d++;
        }
        if (d == n) {
            cout << gold << endl;
        } else {
            cout << "Loowater is doomed!" << endl;
        }
    }

    return 0;
}