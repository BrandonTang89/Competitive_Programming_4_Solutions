/**Kattis - amusicalquestion
 * A DP problem that should be simple but took long because skill issue. Its just Knapsack with 2
 * bags. The issue is that we will MLE if we do it Top Down so we need to do it Bottom Up with the
 * memory saving strategy.
 *
 * dp(a, b, i) is the <sum of wasted space, difference in remaining space> where a is the remaining
 * space in the first bag and b is the remaining space in the second bag and i is the index of the
 * current item we are considering.
 *
 * While the question initially seems like we need to compute not just the sum but also recover the
 * actual solution, this is actually false because we can recover the weights of either bag by doing
 * math on the sum and difference. We also use the representation since it allows us to use standard
 * comparison operators on the tuple (since we are trying to minimise the wasted space first and
 * then the difference)
 *
 * We also can cut down half the state space due to symmetry, i.e. dp(a, b, i) = dp(b, a, i).
 *
 * Time: O(n * c^2), Mem: O(c^2)
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

int c, n;
vector<int> arr;
tuple<int, int> memo[1001][1001]
                    [2];  // memo[a][b] = <sum wasted, difference> where a is the remaining cap of
                          // the first bag and b is the remaining cap of the second bag
// 0 <= b <= a <= c

int main()
{
    fast_cin();
    cin >> c >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(arr.begin(), arr.end(), greater<int>());

    for (int a = 0; a <= c; a++) {
        for (int b = 0; b <= a; b++) {
            memo[a][b][n & 1] = make_tuple(a + b, a - b);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int a = 0; a <= c; a++) {
            for (int b = 0; b <= a; b++) {
                memo[a][b][i & 1] = memo[a][b][(i + 1) & 1];
                if (a >= arr[i]) {
                    int newA = a - arr[i];
                    int newB = b;
                    if (newA < newB) swap(newA, newB);
                    memo[a][b][i & 1] = min(memo[a][b][i & 1], memo[newA][newB][(i + 1) & 1]);
                }
                if (b >= arr[i]) {
                    int newA = a;
                    int newB = b - arr[i];
                    if (newA < newB) swap(newA, newB);
                    memo[a][b][i & 1] = min(memo[a][b][i & 1], memo[newA][newB][(i + 1) & 1]);
                }
            }
        }
    }

    int sumWasted = get<0>(memo[c][c][0]);  // c - a + c - b
    int diff = get<1>(memo[c][c][0]);

    int realSum = 2 * c - sumWasted;  // a + b
    // b - a = diff
    int b = (realSum + diff) / 2;
    int a = realSum - b;

    cout << b << " " << a << endl;
    return 0;
}