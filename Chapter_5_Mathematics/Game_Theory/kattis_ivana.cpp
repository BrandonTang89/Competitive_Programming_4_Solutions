/**Kattis - ivana
 * Simple mini-max problem with DP. The only non-standard part is we need to repeat the game for all
 * possible starting positions. The nice way to deal with this is to use a deque and assume we take
 * the last element and play on the elements [0..n-2] and rotate the deque n times.
 * 
 * Time: O(n^3), Space: O(n^2)
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

int n;
deque<int> arr;
vector<vector<vector<int>>> memo;

int dp(int left, int right, int player)
{
    if (left > right) return 0;
    if (memo[left][right][player] != -1e9) return memo[left][right][player];

    int ans;
    if (player == 0) {  // z is playing to maximise
        ans = max(dp(left + 1, right, 1) + arr[left], dp(left, right - 1, 1) + arr[right]);
    }
    else {  // z is playing to minimise
        ans = min(dp(left + 1, right, 0) - arr[left], dp(left, right - 1, 0) - arr[right]);
    }
    return memo[left][right][player] = ans;
}
int main()
{
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i] = arr[i] % 2;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        memo.assign(n, vector<vector<int>>(n, vector<int>(2, -1e9)));
        if (dp(0, n - 2, 0) < arr[n - 1]) {  // z will lose
            ans++;
        }
        arr.push_back(arr.front());
        arr.pop_front();
    }
    cout << ans << endl;

    return 0;
}