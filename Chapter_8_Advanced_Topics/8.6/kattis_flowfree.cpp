/**Kattis - flowfree
 * A pretty long and scary problem. We need to deal with 2 main parts: complete search
 * and longest path. We use recursive backtracking to try all combinations of colours on
 * the white squares. For each possible arrangement, we check whether the sum of the longest path
 * between the end points of each colour fills the entire grid. Note that we need to write our
 * longest path to return -INF if there is no longest valid path. We use the time saving technique
 * of using a last_used array to avoid re-initialising the memo array. Also we need to write a
 * adjlist manually for each grid cell... tedious.
 * 
 * Time: O(max(3^10,4^8) * 16*2^16) But actually much better because of pruning early and often.
 * Space: O(16*2^16)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int num_colours = 3;
char grid[4][4];
int nodes[16];
vector<int> end_points[4];  // {R,G,B,Y}
map<char, int> colours = {{'R', 0}, {'G', 1}, {'B', 2}, {'Y', 3}, {'W', 4}};
int cti(int r, int c) { return r * 4 + c; }
int memo[16][(1 << 16)];  // current pos, mask
int di[] = {+1, -1, +4, -4};
int last_used[16][(1 << 16)];
int use = 0;
vector<int> adjlist[16] = {
    {1, 4},        {0, 2, 5},   {1, 3, 6},    {2, 7},         {0, 5, 8},      {1, 4, 6, 9},
    {2, 5, 7, 10}, {3, 6, 11},  {4, 9, 12},   {5, 8, 10, 13}, {6, 9, 11, 14}, {7, 10, 15},
    {8, 13},       {9, 12, 14}, {10, 13, 15}, {11, 14},
};

int dp(int pos, int mask, int colour) {
    if (last_used[pos][mask] == use) return memo[pos][mask];
    last_used[pos][mask] = use;
    if (pos == end_points[colour][1]) return memo[pos][mask] = __builtin_popcount(mask);
    int ans = -1000;  // -INF
    for (auto npos : adjlist[pos]) {
        if (nodes[npos] != colour) continue;  // we can only traverse our own colour
        if (mask & (1 << npos)) continue;     // we can't traverse a node twice

        ans = max(ans, dp(npos, mask | (1 << npos), colour));
    }
    return memo[pos][mask] = ans;
};
int longest_path(int colour) {
    int mask = (1 << end_points[colour][0]);
    return dp(end_points[colour][0], mask, colour);
}

bool check() {  // determine if the state of the board is solved
    use++;
    int total_space_covered = 0;
    for (int i = 0; i < num_colours; i++) {
        total_space_covered += longest_path(i);
        if (total_space_covered < 2) return false;
    }
    if (total_space_covered == 16) {
        return true;
    }
    return false;
}

bool search(int node) {  // complete search (brute force)
    if (node == 16) {
        return check();
    }
    if (nodes[node] == 4) {  // white node
        for (int i = 0; i < num_colours; i++) {
            nodes[node] = i;
            if (search(node + 1)) return true;
        }
        nodes[node] = 4;
        return false;
    } else {
        return search(node + 1);
    }
}

int main() {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            cin >> grid[r][c];
            nodes[cti(r, c)] = colours[grid[r][c]];
            if (grid[r][c] == 'Y') num_colours = 4;

            if (nodes[cti(r, c)] != 4) {
                end_points[nodes[cti(r, c)]].push_back(cti(r, c));
            }
        }
    }

    cout << (search(0) ? "solvable" : "not solvable") << endl;

    return 0;
}