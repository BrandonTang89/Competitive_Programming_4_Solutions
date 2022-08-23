/**Kattis - brickwall
 * We let dp(c1, c2, c3) be 1 if we can reach the end with c1, c2, c3 of each brick left and 0
 * otherwise. We recover the parameter of (current position) by comparing the initial number of each
 * brick to current number of bricks.
 *
 * Time: O(n + c1*c2*c3), Space: O(n + c1*c2*c3)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
int t1, t2, t3;
vector<int> arr;
int total_dist;
int memo[302][302][302];
int dp(int c1, int c2, int c3) {
    if (memo[c1][c2][c3] != -1) return memo[c1][c2][c3];
    int cur_pos = (t1 - c1) + (t2 - c2) * 2 + (t3 - c3) * 3;
    int &ans = memo[c1][c2][c3];
    if (cur_pos == total_dist)
        return ans = 1;
    else if (cur_pos > 0 && arr[cur_pos] != arr[cur_pos - 1])
        return ans = 0;

    if (c1 > 0) {
        if (dp(c1 - 1, c2, c3)) return ans = 1;
    }
    if (c2 > 0) {
        if (dp(c1, c2 - 1, c3)) return ans = 1;
    }
    if (c3 > 0) {
        if (dp(c1, c2, c3 - 1)) return ans = 1;
    }
    return ans = 0;
}
int main() {
    memset(memo, -1, sizeof memo);
    cin >> n >> t1 >> t2 >> t3;
    total_dist = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        total_dist += x;
        while (x--) {
            arr.push_back(i);
        }
    }

    if (dp(t1, t2, t3))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}