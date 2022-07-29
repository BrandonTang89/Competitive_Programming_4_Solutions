/**Kattis - daceydice
 * State Space Flood Fill / DFS. Each state is (row, col, num on top, num on right), transitions are
 * going to the left, right, up and down. However, I neede to manually write out how the numbers on
 * the dice would change with each transition... 
 * 
 * Time: O(N^2 * 6^2 * 4), Space: O(N^2 + 6^2 * 4)
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

int dr[4] = {0, 0, -1, 1};
int dc[4] = {1, -1, 0, 0};
pair<int, int> Tran[6][6][4];

int n, num_tc;
int sr, sc, er, ec;
vector<vector<char>> grid;

int visited[21][21][6][6];
void dfs(int r, int c, int top, int right) {
    if (visited[r][c][top][right]) return;
    // cout << r << " " << c << " " << top << " " << right << endl;
    visited[r][c][top][right] = 1;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
        if (grid[nr][nc] == '*') continue;
        dfs(nr, nc, Tran[top][right][i].first, Tran[top][right][i].second);
    }
}
void popTran() {
    Tran[0][1][0] = {4, 0};
    Tran[0][1][1] = {1, 5};
    Tran[0][1][2] = {2, 1};
    Tran[0][1][3] = {3, 1};

    Tran[0][2][0] = {3, 0};
    Tran[0][2][1] = {2, 5};
    Tran[0][2][2] = {4, 2};
    Tran[0][2][3] = {1, 2};

    Tran[0][3][0] = {2, 0};
    Tran[0][3][1] = {3, 5};
    Tran[0][3][2] = {1, 3};
    Tran[0][3][3] = {4, 3};

    Tran[0][4][0] = {1, 0};
    Tran[0][4][1] = {4, 5};
    Tran[0][4][2] = {3, 4};
    Tran[0][4][3] = {2, 4};

    Tran[1][0][0] = {5, 1};
    Tran[1][0][1] = {0, 4};
    Tran[1][0][2] = {3, 0};
    Tran[1][0][3] = {2, 0};

    Tran[1][2][0] = {3, 1};
    Tran[1][2][1] = {2, 4};
    Tran[1][2][2] = {0, 2};
    Tran[1][2][3] = {5, 2};

    Tran[1][3][0] = {2, 1};
    Tran[1][3][1] = {3, 4};
    Tran[1][3][2] = {5, 3};
    Tran[1][3][3] = {0, 3};

    Tran[1][5][0] = {0, 1};
    Tran[1][5][1] = {5, 4};
    Tran[1][5][2] = {2, 5};
    Tran[1][5][3] = {3, 5};

    Tran[2][0][0] = {5, 2};
    Tran[2][0][1] = {0, 3};
    Tran[2][0][2] = {1, 0};
    Tran[2][0][3] = {4, 0};

    Tran[2][1][0] = {4, 2};
    Tran[2][1][1] = {1, 3};
    Tran[2][1][2] = {5, 1};
    Tran[2][1][3] = {0, 1};

    Tran[2][4][0] = {1, 2};
    Tran[2][4][1] = {4, 3};
    Tran[2][4][2] = {0, 4};
    Tran[2][4][3] = {5, 4};

    Tran[2][5][0] = {0, 2};
    Tran[2][5][1] = {5, 3};
    Tran[2][5][2] = {4, 5};
    Tran[2][5][3] = {1, 5};

    Tran[3][0][0] = {5, 3};
    Tran[3][0][1] = {0, 2};
    Tran[3][0][2] = {4, 0};
    Tran[3][0][3] = {1, 0};

    Tran[3][1][0] = {4, 3};
    Tran[3][1][1] = {1, 2};
    Tran[3][1][2] = {0, 1};
    Tran[3][1][3] = {5, 1};

    Tran[3][4][0] = {1, 3};
    Tran[3][4][1] = {4, 2};
    Tran[3][4][2] = {5, 4};
    Tran[3][4][3] = {0, 4};

    Tran[3][5][0] = {0, 3};
    Tran[3][5][1] = {5, 2};
    Tran[3][5][2] = {1, 5};
    Tran[3][5][3] = {4, 5};

    Tran[4][0][0] = {5, 4};
    Tran[4][0][1] = {0, 1};
    Tran[4][0][2] = {2, 0};
    Tran[4][0][3] = {3, 0};

    Tran[4][2][0] = {3, 4};
    Tran[4][2][1] = {2, 1};
    Tran[4][2][2] = {5, 2};
    Tran[4][2][3] = {0, 2};

    Tran[4][3][0] = {2, 4};
    Tran[4][3][1] = {3, 1};
    Tran[4][3][2] = {0, 3};
    Tran[4][3][3] = {5, 3};

    Tran[4][5][0] = {0, 4};
    Tran[4][5][1] = {5, 1};
    Tran[4][5][2] = {3, 5};
    Tran[4][5][3] = {2, 5};

    Tran[5][1][0] = {4, 5};
    Tran[5][1][1] = {1, 0};
    Tran[5][1][2] = {3, 1};
    Tran[5][1][3] = {2, 1};

    Tran[5][2][0] = {3, 5};
    Tran[5][2][1] = {2, 0};
    Tran[5][2][2] = {1, 2};
    Tran[5][2][3] = {4, 2};

    Tran[5][3][0] = {2, 5};
    Tran[5][3][1] = {3, 0};
    Tran[5][3][2] = {4, 3};
    Tran[5][3][3] = {1, 3};

    Tran[5][4][0] = {1, 5};
    Tran[5][4][1] = {4, 0};
    Tran[5][4][2] = {2, 4};
    Tran[5][4][3] = {3, 4};
}
int main() {
    popTran();
    // 0, roll right, 1, roll left, 2, roll up, 3, roll down
    cin >> num_tc;
    while (num_tc--) {
        cin >> n;
        grid.assign(n, vector<char>(n, '.'));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } else if (grid[i][j] == 'H') {
                    er = i;
                    ec = j;
                }
            }
        }
        memset(visited, 0, sizeof(visited));
        dfs(sr, sc, 0, 1);

        bool can_reach = false;
        for (int i = 0; i <= 5; i++) {
            if (visited[er][ec][1][i]) {
                can_reach = true;
                break;
            }
        }
        if (can_reach) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}