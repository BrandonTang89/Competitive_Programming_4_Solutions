/**Kattis - goodmorning
 * Relatively simple backtracking problem.
 * 
 * Time: O(1000) since we get to at most 4 digits of numbers, Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> adjlist[10];

int backtrack(int n, int pos, int cur_val) { // returns the closest value to n, assuming we already at cur_val
    if (cur_val >= n) {
        return cur_val;
    }
    if (cur_val == 0 && pos == 0) { // edge base case
        return 0;
    }
    int best = cur_val;
    int smallest_difference = abs(cur_val - n);
    for (auto i: adjlist[pos]){
        int new_val;
        if (i == pos)
             new_val = backtrack(n, i, cur_val*10+i); // prevent infinite loops
        else
            new_val = backtrack(n, i, cur_val); // allow for not pressing i but moving to it
        int new_difference = abs(new_val - n);
        if (new_difference < smallest_difference) {
            smallest_difference = new_difference;
            best = new_val;
        }
    }
    return best;
}
int main() {
    adjlist[0] = {0};
    adjlist[1] = {1, 4, 2};
    adjlist[2] = {2, 3, 5};
    adjlist[3] = {3, 6};
    adjlist[4] = {4, 5, 7};
    adjlist[5] = {5, 6, 8};
    adjlist[6] = {6, 9};
    adjlist[7] = {7, 8};
    adjlist[8] = {8, 0, 9};
    adjlist[9] = {9};

    int num_tc = 0;
    cin >> num_tc;
    for (int i = 0; i < num_tc; i++) {
        int n;
        cin >> n;
        cout << backtrack(n, 1, 0) << endl;
    }
    return 0;
}