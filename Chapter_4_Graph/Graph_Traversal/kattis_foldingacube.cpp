/**Kattis - foldingacube
 * State Space Flood Fill / DFS. Each state is (row, col, num on top, num on right), transitions are
 * going to the left, right, up and down.
 *
 * Observe that we should assume a random starting orientation at a randomly selected initial
 * position in the net. Then if we are able to flood fill with the rolling transitions such that
 * each of the faces show up on the top of the cube at a certain position, the net can be folded
 * into a cube.
 *
 * Time: O(1), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;


int n, num_tc;
int sr, sc, er, ec;
vector<vector<char>> grid;

int visited[6][6][6][6];

// 0: Right, 1: Left, 2: Up, 3: Down
int dr[4] = {0, 0, -1, 1};
int dc[4] = {1, -1, 0, 0};
pair<int, int> Tran[6][6][4]; // Tran[top][right][direction] = {new top, new right}
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
void dfs(int r, int c, int top, int right) {
    if (visited[r][c][top][right]) return;
    visited[r][c][top][right] = 1;
    done.insert(top);
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
        if (grid[nr][nc] == '.') continue;
        dfs(nr, nc, Tran[top][right][i].first, Tran[top][right][i].second);
    }
}
unordered_set<int> done;
int main() {
    popTran();
    // 0, roll right, 1, roll left, 2, roll up, 3, roll down
    n = 6;

    grid.assign(n, vector<char>(n, '.'));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '#') {
                sr = i;
                sc = j;
            }
        }
    }
    memset(visited, 0, sizeof(visited));
    dfs(sr, sc, 0, 1);

    if (done.size() == 6) {
        cout << "can fold" << endl;
    } else {
        cout << "cannot fold" << endl;
    }
    return 0;
}