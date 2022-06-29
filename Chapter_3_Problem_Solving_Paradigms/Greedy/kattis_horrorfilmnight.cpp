/**Kattis - horrorfilmnight
 * First observe that we can ignore all the shows that neither of them enjoy. Then notice that we
 * should take all the show that both of them like. Between such shows, assume we are given the
 * sequence 101101110 where each number represents each other liking the show (but not the other).
 * Observe that we can simplify this into 101010. Then notice that we should just take the first
 * possible one, ie a greedy strategy. Just translate this into an actually implementable algorithm
 * by using variables that point to the location along each of the 2 arrays that we are considering.
 *
 * Time: O(n log n), Space: O(n)
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

int n, m;
vector<int> a, b;
int main() {
    fast_cin();
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    cin >> m;
    b.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(b.begin(), b.end());

    a.emplace_back(1000000);
    b.emplace_back(1000000);

    int state = 0;  // both, 1 or 2
    int l = 0, r = 0;
    int ans = 0;

    while (l < n + 1 && r < m + 1) {
        if (a[l] < b[r]) {
            // left coming first
            if (l == n) break;
            if (state == 0 || state == 2) {
                state = 1;
                ans++;
            }
            l++;
        } else if (a[l] > b[r]) {
            // right coming first
            if (r == m) break;
            if (state == 0 || state == 1) {
                state = 2;
                ans++;
            }
            r++;
        } else {
            // equal
            if (l == n || r == m) break;
            state = 0;
            ans++;
            l++;
            r++;
        }
    }
    cout << ans << endl;

    return 0;
}