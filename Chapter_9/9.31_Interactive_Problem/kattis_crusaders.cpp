/**Kattis - crusaders
 * Interesting enough binary search, interactive problem. Essentially we just process the
 * applications in order (doesn't affect much), then binary search. Note that after we
 * process the first i applications, we already have a database of city information, we 
 * can binary search that information database to get the upper and lower bounds of the
 * possible cities in processing the i+1th application. This gets you 95% of the way there,
 * the last 5% is the small optimisation commented below.
 * 
 * Time: O(?), Space: O(A)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int A, C;
int money_left = 1500;
vector<pair<int, int>> S;
vector<int> ans;  // ans[i] is the city the ith pony should live in
unordered_map<int, int> memo;
set<pair<int, int>> cities;  // {cost, index}

void get(int x) {
    // cout << "gettting " << x << endl;
    int income = S[x].first;
    int lo, hi;
    if (cities.lower_bound({income, 0})->first > income) {
        hi = cities.lower_bound({income, 0})->second -1; // looks insignificant, but actually impt
        // if > income, it can't be part of the range, so we can mildly reduce the search space
    }
    else {
        hi = cities.lower_bound({income, 0})->second;
    }
    lo = (--cities.upper_bound({income, 0}))->second;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        int res;
        if (memo.count(mid) == 0) {
            assert(money_left > 0);
            money_left--;
            cout << "Q " << mid << endl << flush;
            cin >> res;
            memo[mid] = res;
            cities.insert({res, mid});
        } else {
            res = memo[mid];
        }

        if (res == income) {  // we luckily found the best city
            lo = hi = mid;
            break;
        } else if (res < income) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    ans[S[x].second] = lo;
}
int main() {
    cin >> C >> A;

    for (int i = 0; i < A; i++) {
        int x;
        cin >> x;
        S.emplace_back(x, i);
    }
    ans.assign(A, -1);

    // Just assume city 1 is free
    cities.insert({-1, 1});
    memo[1] = -1;

    // Get the cost of the last city
    cout << "Q " << C << endl << flush;
    int res;
    cin >> res;
    cities.insert({res, C});

    for (int i=0; i<A; i++) {
        get(i);
    }
    cout << "A ";
    for (int i = 0; i < A; i++) {
        assert(ans[i] != -1);
        cout << ans[i] << " ";
    }
    cout << endl << flush;

    return 0;
}