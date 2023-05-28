/**Kattis - gridgame
 * Binary search + MCBM. We binary search for the maximum minimum value that it is still possible to
 * select n cells with pairwise different cols and rows. To do a check, we can model the problem as 
 * a MCBM problem where we are trying to match the rows to the columns and there is an edge iff we 
 * can select the cell with that row and that column. We then check if MCBM = n.
 * 
 * Time: O(n^3 log 1e6), Mem: O(n^2)
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
vector<vector<int>> grid;
vector<vector<int>> adjlist;
vector<int> match, visited;
int aug(int L)
{
    if (visited[L]) return 0;
    visited[L] = 1;
    for (auto &R : adjlist[L]) {
        if (match[R] == -1 || aug(match[R])) {
            match[R] = L;
            match[L] = R;
            return 1;
        }
    }
    return 0;
}
int cal_MCBM(int Vleft, int Vright)
{
    match.assign(Vleft + Vright, -1);
    unordered_set<int> freeV;
    for (int L = 0; L < Vleft; L++) freeV.emplace(L);
    int MCBM = 0;

    for (int L = 0; L < Vleft; L++) {  // all left vectices
        vector<int> candidates;
        for (auto R : adjlist[L]) {  // all right vectices neighbouring u
            if (match[R] == -1) {    // if v is unassigned
                candidates.push_back(R);
            }
        }
        if ((int)candidates.size() > 0) {
            MCBM++;
            freeV.erase(L);
            int a = rand() % candidates.size();
            match[candidates[a]] = L;
            match[L] = candidates[a];
        }
    }

    // MCBM Calculation
    for (auto &L : freeV) {
        visited.assign(Vleft, 0);
        MCBM += aug(L);
    }

    return MCBM;
}

bool possible(int mini)
{
    adjlist.assign(n * 2, vector<int>());

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (grid[r][c] >= mini) {
                adjlist[r].push_back(n + c);
            }
        }
    }

    return cal_MCBM(n, n) == n;
}
int main()
{
    fast_cin();
    cin >> n;
    grid.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    int l = 0, r = 1e6;
    // binary search for the minimum

    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (possible(mid)) {  // can go up
            l = mid;
        }
        else {
            r = mid - 1;
        }
    }

    cout << l << endl;
    return 0;
}