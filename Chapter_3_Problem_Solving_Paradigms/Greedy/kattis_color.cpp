/**Kattis - color
 * It should be obvious that we should first sort the socks. Then observe that one washing machine
 * needs to wash the leftmost sock. To achieve optimality, we should put as many socks into that as
 * possible, from left to right (greedy). Now we have a sub-problem with another leftmost sock, so
 * we repeat.
 *
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, c, k;
vector<int> v;
int main() {
    cin >> n >> c >> k;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());

    int ans = 1, cur_min = v[0], cur_size = 1;
    for (int i = 1; i < n; i++) {
        if (v[i] - cur_min > k || cur_size >= c) {
            // new washing machine
            ans++;
            cur_min = v[i];
            cur_size = 1;
        } else {
            cur_size++;
        }
    }
    cout << ans << endl;

    return 0;
}