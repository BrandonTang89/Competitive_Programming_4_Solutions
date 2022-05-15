/**Kattis - aspenavenue
 * This supposed to be a decently easy problem, but i ran into a bug that I spend quite long
 * fixing. The main observation is a greedy one: given 2 trees on the left side, a < b.
 * a will come before b in the sorted list of pre-planted trees. Why? else we can use the
 * exchange argument that we just swap a and b and itll be no worse off. Same argument
 * for right side.
 * 
 * As such, we know that the first tree in the sorted list of planted trees must either be 
 * the first of the left or right sides. Generally, after placing l_done and r_done trees,
 * the (l_done + r_done)th (0 index) tree must either be the next left or next right tree.
 * 
 * From here, we can easily construct the DP states and transitions. Also notice how we recover
 * the parameter of "how many trees already placed" from the other 2 parameters to improve from
 * O(n^3) to O(n^2).
 * 
 * Time: O(n^2), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, L, W;
ld EPS = 1e-12;
ld INF = LLONG_MAX;
vector<int> trees;

ld distance_of_tree(int num_tree) { return (num_tree * L / (ld)((n / 2) - 1)); }
// this (ld) is important and easy to miss and thus cause 1 hour of wasted debugging time

ld memo[1009][1009];
ld dp(int l_done, int r_done) {  // euclidean distance needed after doing (l_done, r_done) trees
    if (l_done == n / 2 && r_done == n / 2) return 0;

    if (abs(memo[l_done][r_done] - (-1)) > EPS) return memo[l_done][r_done];  // != -1
    ld ans = INF;

    int next_tree = l_done + r_done;
    if (l_done < n / 2) {
        ans = min(ans, dp(l_done + 1, r_done) + abs(distance_of_tree(l_done) - trees[next_tree]));
    }
    if (r_done < n / 2) {
        ans = min(ans,
                  dp(l_done, r_done + 1) + sqrt((distance_of_tree(r_done) - trees[next_tree]) *
                                                    (distance_of_tree(r_done) - trees[next_tree]) +
                                                (W * W)));
    }
    return memo[l_done][r_done] = ans;
}
int main() {
    fast_cin();
    while (cin >> n >> L >> W) { // we use a while loop to allow for the UVA format of test cases
        trees.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> trees[i];
        }
        sort(trees.begin(), trees.end());
        for (int i = 0; i <= n / 2 + 1; i++) {
            for (int j = 0; j <= n / 2 + 1; j++) {
                memo[i][j] = -1;
            }
        }

        cout << fixed << setprecision(15) << dp(0, 0) << endl;
    }

    return 0;
}