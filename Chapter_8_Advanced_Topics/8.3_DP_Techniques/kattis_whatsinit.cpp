/**Kattis - whatisinit
 * Relatively tricky DP problem. We define 2 dp functions: possible_to_be_up(i, cur, amt) and
 * possible_to_be_down(i, cur, amt). These together check if it is possible to have the ith
 * ingredient be cur and the total amount (percentage) of ingredients from [0:cur] be amt. Both of
 * them should only be called on arguments where 0 <= cur <= amt <= 100 (and they will maintain this
 * pre-condition on their recursive calls).
 * The first does the check upwards, i.e. whether the ingredients before i can be selected such that
 * at i, we have (cur, amt) and by the time we get to the first element, we have (cur == amt) so
 * that at the "0th" element we have cur=amt=0. The second does the check downwards, i.e. whether
 * the ingredients after i can be selected such that by the last element, amt = 100.
 * You can read the code for more details on the basecases and recurrences.
 *
 * Time is actually slightly tight, if we explore the entire state space then we will TLE. As such,
 * we ensure to only explore the state space where (cur <= amt) which roughly halves the state
 * space.
 *
 * Time: O(N*101^3), Space: O(N*101^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
vector<string> ingredients;
vector<int> fi;
vector<vector<vector<int>>> memoup, memodown;

// Precondition: 0 <= i < n, 0 <= cur <= amt <= 100
int possible_to_be_up(int i, int cur, int amt)
{
    int &ans = memoup[i][cur][amt];
    if (ans != -1) return ans;
    if (fi[i] != -1 && fi[i] != cur) return ans = 0;
    if (i == 0) return (ans = (cur == amt) ? 1 : 0);

    int new_amt = amt - cur;
    for (int j = cur; j <= new_amt; j++) {
        if (possible_to_be_up(i - 1, j, new_amt)) {
            return (ans = 1);
        }
    }

    return (ans = 0);
}

// Precondition: 0 <= i < n, 0 <= cur <= amt <= 100
int possible_to_be_down(int i, int cur, int amt)
{
    int &ans = memodown[i][cur][amt];
    if (ans != -1) return ans;
    if (fi[i] != -1 && fi[i] != cur) return ans = 0;
    if (i == n - 1) return (ans = (amt == 100) ? 1 : 0);

    for (int j = min(cur, 100 - amt); j >= 0; j--) {
        if (possible_to_be_down(i + 1, j, amt + j)) {
            return (ans = 1);
        }
    }

    return (ans = 0);
}

int main()
{
    cin >> n;
    ingredients.resize(n);
    fi.resize(n);
    memoup.assign(n, vector<vector<int>>(101, vector<int>(101, -1)));
    memodown.assign(n, vector<vector<int>>(101, vector<int>(101, -1)));
    for (int i = 0; i < n; i++) {
        cin >> ingredients[i];
        string s;
        cin >> s;

        if (s == "?") {
            fi[i] = -1;
        }
        else {
            fi[i] = stoi(s);
        }
    }

    int max_cur = 100;
    for (int i = 0; i < n; i++) {
        int mini = INT_MAX;
        int maxi = INT_MIN;
        for (int j = 0; j <= max_cur; j++) {
            for (int amt = j; amt <= 100; amt++) {
                if (possible_to_be_up(i, j, amt) && possible_to_be_down(i, j, amt)) {
                    mini = min(mini, j);
                    maxi = max(maxi, j);
                }
            }
        }
        cout << ingredients[i] << " " << mini << " " << maxi << endl;

        if (fi[i] != -1) {
            max_cur = min(max_cur, fi[i]);
        }
    }

    return 0;
}