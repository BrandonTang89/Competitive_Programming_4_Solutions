/**Kattis - peggamefortwo
 * Generic negamax problem. Pre-generate the transitions (using python script below) and represent
 * game state as a vector of 15 ints. We can use an explicit stack to avoid copying the game states
 * too many times.
 * 
 * Time: O(?), Space: O(15^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

vector<tuple<int, int, int>> transitions{
    {0, 1, 3},    {0, 2, 5},    {1, 3, 6},    {1, 4, 8},    {2, 4, 7},    {2, 5, 9},
    {3, 1, 0},    {3, 4, 5},    {3, 6, 10},   {3, 7, 12},   {4, 7, 11},   {4, 8, 13},
    {5, 8, 12},   {5, 4, 3},    {5, 2, 0},    {5, 9, 14},   {6, 3, 1},    {6, 7, 8},
    {7, 4, 2},    {7, 8, 9},    {8, 7, 6},    {8, 4, 1},    {9, 8, 7},    {9, 5, 2},
    {10, 6, 3},   {10, 11, 12}, {11, 7, 4},   {11, 12, 13}, {12, 8, 5},   {12, 13, 14},
    {12, 11, 10}, {12, 7, 3},   {13, 12, 11}, {13, 8, 4},   {14, 13, 12}, {14, 9, 5},
};
vector<vector<int>> st;

int nega(int depth)
{
    // cout << depth << endl;
    int ans = -1e9;
    int nextDepth = depth + 1;
    st[nextDepth] = st[depth];
    for (auto &[x, y, z] : transitions) {
        if (st[depth][x] && st[depth][y] && !st[depth][z]) {
            st[nextDepth][x] = 0;
            st[nextDepth][y] = 0;
            st[nextDepth][z] = st[depth][x];

            // cout << x << " " << y << " " << z << endl;
            ans = max(ans, st[depth][x] * st[depth][y] - nega(depth + 1));
            st[nextDepth][x] = st[depth][x];
            st[nextDepth][y] = st[depth][y];
            st[nextDepth][z] = 0;
        }
    }
    assert(st[depth] == st[nextDepth]);
    if (ans == -1e9) return 0;
    return ans;
}

int main()
{
    st.assign(17, vector<int>(15, 0));
    for (int i = 0; i < 15; i++) cin >> st[0][i];
    cout << nega(0) << endl;
    return 0;
}

/*
board = [
    [0],
    [1,2],
    [3,4,5],
    [6,7,8,9],
    [10,11,12,13,14]
]

dr = [-1, 0, 1, 0, -1, 1]
dc = [0, 1, 0, -1, -1, 1]

print('{', end=' ')
for r in range(5):
    print()
    for c in range(r+1):
        for i in range(6):
            try: # x jump over y to z
                if r+2*dr[i] < 0 or c+2*dc[i] < 0:
                    continue
                z = board[r+2*dr[i]][c+2*dc[i]]
                y = board[r+dr[i]][c+dc[i]]
                x = board[r][c]
                # print(x, y, z)
                print(f'{{{x}, {y}, {z}}},', end=' ')
            except:
                pass
print('}')
*/