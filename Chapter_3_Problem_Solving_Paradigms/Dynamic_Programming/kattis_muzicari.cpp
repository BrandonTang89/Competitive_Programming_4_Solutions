/**Kattis - muzicari
 * Quite an interesting 0-1 knapsack variant, notice that the toilet effectively has 2
 * cubicles, so for each person we just assign either cubicle a or b. The order of who
 * goes into cubicle a is irrelevant, likewise for b.
 *
 * Let dp(index, rt) be the minimum time that is used for cubicle b given that we have already
 * assigned index people and that we can only assign rt worth of time to cubicle a. We then
 * have a knapsack like transition, either take into stall a (put into the knapsack) or stall b
 * (don't put into the sack).
 *
 * We need to print the actual solution, not just whether it's possible. As such, we use an
 * auxillary function that checks which transition is the right one, hitting target amount of time
 * used for stall b.
 * 
 * Time: O(nT), Space: O(nT)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, INF = 1e9, T;
vector<int> arr;
int memo[505][5005];
int dp(int index, int rt) {  // minimum time in the second slot, assuming first slot has rt left
    if (rt < 0) return INF;
    if (index == n && rt >= 0) return 0;
    int &ans = memo[index][rt];
    if (ans != -1) return ans;
    if (rt < arr[index]) {  // cannot contain current item
        return ans = arr[index] + dp(index + 1, rt);
    }

    // Select whether or not to take
    return ans = min(dp(index + 1, rt) + arr[index], dp(index + 1, rt - arr[index]));
}
int target, atime = 0, btime = 0;
void get_sol(int index, int rt) {
    if (index == n) return;

    if (rt < arr[index]) {
        // cannot take in a, take in b instead
        cout << btime << " ";
        btime += arr[index];
        target -= arr[index];
        get_sol(index + 1, rt);
    } else {
        if (target == dp(index + 1, rt - arr[index])) {
            // take in a
            cout << atime << " ";
            atime += arr[index];
            get_sol(index + 1, rt - arr[index]);
        } else {
            // take in b
            cout << btime << " ";
            btime += arr[index];
            target -= arr[index];
            get_sol(index + 1, rt);
        }
    }
}
int main() {
    cin >> T >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    memset(memo, -1, sizeof memo);
    target = dp(0, T);

    get_sol(0, T);
    cout << endl;

    return 0;
}