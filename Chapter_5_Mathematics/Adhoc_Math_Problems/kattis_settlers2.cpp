/**Kattis - settlers2
 * Tedious pre-computation problem. We just construct the hexagonal grid as a regular grid but with
 * 6 directions of edges. Then we simulate the building of the grid and store each number created in
 * a vector.
 *
 * Time: O(10000), Mem: O(10000)
 * */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

vector<int> counts(5, 0);
vector<vector<int>> grid(300, vector<int>(300, -1));
vector<int> ans(10005, -1);
int dr[] = {-1, -1, 0, 1, 1, 0};
int dc[] = {0, -1, -1, 0, 1, 1};
int created = 1;

inline int getNewNumber(int x, int y)
{
    // <-- here we can check how big of a grid we need -->
    // if (created > 9990) {
    //     cout << x << " " << y << endl;
    // }
    int minNum = -1;
    int minCount = INT_MAX;
    for (int i = 0; i < 5; i++) {
        // check if i is a neighbour
        bool valid = true;
        for (int j = 0; j < 6; j++) {
            int newx = x + dr[j];
            int newy = y + dc[j];
            if (grid[newx][newy] == i) {
                valid = false;
                break;
            }
        }
        if (valid) {
            if (counts[i] < minCount) {
                minCount = counts[i];
                minNum = i;
            }
        }
    }

    grid[x][y] = minNum;
    counts[minNum] += 1;
    ans[created] = minNum;
    created++;

    return minNum;
}
int main()
{
    int x = 150, y = 150;

    grid[x][y] = 0;
    counts[0] += 1;
    ans[0] = 0;

    for (int k = 1; created <= 10000; k++) {
        x = x + dr[5];
        y = y + dc[5];
        getNewNumber(x, y);

        for (int i = 0; i < 6 && created <= 10000; i++) {
            for (int j = 0; j < k && created <= 10000; j++) {
                if (i == 0 && j == k - 1) break;
                x = x + dr[i];
                y = y + dc[i];
                getNewNumber(x, y);
            }
        }
    }

    // for (int r = 480; r < 520; r++){
    //     for (int c = 480; c < 520; c++){
    //         char ch = ((grid[r][c] == -1) ? '_' : '0' + grid[r][c]);
    //         if (r == 500 && c == 500) ch = 'X';
    //         cout << ch  << " ";
    //     }
    //     cout << endl;
    // }

    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        cout << ans[n - 1] + 1 << endl;
    }

    return 0;
}