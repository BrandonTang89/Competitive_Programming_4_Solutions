/**UVa - 10304: Optimal Binary Search Tree
 * Knuth Optimisation DP. We let dp(i, j) be the cost of constructing the BST with elements from
 * i to j inclusively + the sum of the frequencies from i to j. Then we get that
 * dp(i,j) = min(dp(i,k-1) + dp(k+1,j)) + cost(i, j).
 * 
 * Time: O(n^2), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, INF = 1e9;
vector<int> arr;
int cost(int l, int r) {  // range sum from [l, r]
    if (l > r) return 0;
    if (l == 0) return arr[r];
    return (arr[r] - arr[l - 1]);
}

vector<vector<int>> memo, opt;
int dpKnuth(int i, int j) {
    if (i > j) return 0;
    if (i == j) {
        opt[i][j] = i;
        return memo[i][j] = cost(i, j);
    }
    if (memo[i][j] != -1) return memo[i][j];
    memo[i][j] = INF;

    int start = (j > i ? opt[i][j - 1] : i);
    if (start == -1) start = i;  // if not yet processed that state

    int end = (i < n - 1 ? opt[i + 1][j] : j);
    if (end == -1) end = j;  // if not yet processed that state

    for (int k = start; k <= end; k++) {
        int tcost = dpKnuth(i, k - 1) + dpKnuth(k + 1, j) + cost(i, j);
        if (tcost < memo[i][j]) {
            memo[i][j] = tcost;
            opt[i][j] = k;
        }
    }
    return memo[i][j];
}

int main() {
    while (cin >> n) {
        arr.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            if (i > 0) arr[i] += arr[i - 1];
        }
        memo.assign(n, vector<int>(n, -1));
        opt.assign(n + 1, vector<int>(n + 1, -1));
        cout << dpKnuth(0, n - 1) - cost(0, n - 1) << endl;
    }

    return 0;
}