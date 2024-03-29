/**Kattis - unlockpattern2
 * Extremely tedious question. Had to choose between generating the map programmatically using the
 * geom libary or just doing it by hand. I did it by hand but idk if it was the right choice. The
 * main idea is to generate all possible paths while ensuring that the path is valid. Just use a simple
 * recursive backtracking with pruning to generate all possible paths. Should be quite straightforward.
 * 
 * Time: O(9!), Space: O(9!)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int ans = 0;
string arr;
vector<int> m[9][9][4];
vector<int> allnums = {0, 1, 2, 3, 4, 5, 6, 7, 8};
map<char, int> mp = {{'L', 0}, {'R', 1}, {'S', 2}, {'A', 3}, {'?', -1}};
int cancel[9][9];
// left, right, straight, behind

vector<int> out;  // just for debugging
void rec(int pre, int cur, int bm)
{
    if (bm == 0) {
        ans++;  // no more numbers to go to
        // for (auto i: out){
        //     cout << i << " ";
        // }
        // cout << endl;
    }
    int next_turn = 7 - __builtin_popcount(bm);  // number of numbers left to go to

    vector<int> nextmoves = (mp[arr[next_turn]] == -1) ? allnums : m[pre][cur][mp[arr[next_turn]]];
    for (auto j : nextmoves) {
        if (bm & (1 << j)) {
            if (cancel[cur][j] != -1 && (bm & (1 << cancel[cur][j]))) {
                continue;
            }
            else {
                out.push_back(j);
                rec(cur, j, bm ^ (1 << j));
                out.pop_back();
            }
        }
    }
}
int main()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int j = 0; j < 4; j++) {
                m[i][j][j] = {};
            }
        }
    }
    m[0][1][1] = {3, 4, 5, 6, 7, 8};
    m[0][1][2] = {2};

    m[0][2][1] = {3, 4, 5, 6, 7, 8};

    m[0][3][0] = {1, 2, 4, 5, 7, 8};
    m[0][3][2] = {6};

    m[0][4][0] = {1, 2, 5};
    m[0][4][1] = {3, 6, 7};
    m[0][4][2] = {8};

    m[0][5][0] = {1, 2};
    m[0][5][1] = {3, 4, 6, 7, 8};

    m[0][6][0] = {1, 2, 4, 5, 7, 8};

    m[0][7][0] = {1, 2, 4, 5, 8};
    m[0][7][1] = {3, 6};

    m[0][8][0] = {1, 2, 5};
    m[0][8][1] = {3, 6, 7};

    m[1][0][0] = {3, 4, 5, 6, 7, 8};
    m[1][0][3] = {2};

    m[1][2][1] = {3, 4, 5, 6, 7, 8};
    m[1][2][3] = {0};

    m[1][3][0] = {2, 4, 5, 6, 7, 8};
    m[1][3][1] = {0};

    m[1][4][0] = {2, 5, 8};
    m[1][4][1] = {0, 3, 6};
    m[1][4][2] = {7};

    m[1][5][0] = {2};
    m[1][5][1] = {0, 3, 4, 6, 7, 8};

    m[1][6][0] = {2, 4, 5, 7, 8};
    m[1][6][1] = {0, 3};

    m[1][7][0] = {2, 5, 8};
    m[1][7][1] = {0, 3, 6};

    m[1][8][0] = {2, 5};
    m[1][8][1] = {0, 3, 4, 6, 7};

    m[2][0][0] = {3, 4, 5, 6, 7, 8};

    m[2][1][0] = {3, 4, 5, 6, 7, 8};
    m[2][1][2] = {0};

    m[2][3][0] = {4, 5, 6, 7, 8};
    m[2][3][1] = {0, 1};

    m[2][4][0] = {5, 7, 8};
    m[2][4][1] = {0, 1, 3};
    m[2][4][2] = {6};

    m[2][5][1] = {0, 1, 3, 4, 6, 7};
    m[2][5][2] = {8};

    m[2][6][0] = {5, 7, 8};
    m[2][6][1] = {0, 1, 3};

    m[2][7][0] = {5, 8};
    m[2][7][1] = {0, 1, 3, 4, 6};

    m[2][8][1] = {0, 1, 3, 4, 6, 7};

    m[3][0][1] = {1, 2, 4, 5, 7, 8};
    m[3][0][3] = {6};

    m[3][1][0] = {0};
    m[3][1][1] = {2, 4, 5, 6, 7, 8};

    m[3][2][0] = {0, 1};
    m[3][2][1] = {4, 5, 6, 7, 8};

    m[3][4][0] = {0, 1, 2};
    m[3][4][1] = {6, 7, 8};
    m[3][4][2] = {5};

    m[3][5][0] = {0, 1, 2};
    m[3][5][1] = {6, 7, 8};

    m[3][6][0] = {1, 2, 4, 5, 7, 8};
    m[3][6][3] = {0};

    m[3][7][0] = {0, 1, 2, 4, 5, 8};
    m[3][7][1] = {6};

    m[3][8][0] = {0, 1, 2, 4, 5};
    m[3][8][1] = {6, 7};

    m[4][0][0] = {3, 6, 7};
    m[4][0][1] = {1, 2, 5};
    m[4][0][3] = {8};

    m[4][1][0] = {0, 3, 6};
    m[4][1][1] = {2, 5, 8};
    m[4][1][3] = {7};

    m[4][2][0] = {0, 1, 3};
    m[4][2][1] = {5, 7, 8};
    m[4][2][3] = {6};

    m[4][3][0] = {6, 7, 8};
    m[4][3][1] = {0, 1, 2};
    m[4][3][3] = {5};

    m[4][5][0] = {0, 1, 2};
    m[4][5][1] = {6, 7, 8};
    m[4][5][3] = {3};

    m[4][6][0] = {5, 7, 8};
    m[4][6][1] = {0, 1, 3};
    m[4][6][3] = {2};

    m[4][7][0] = {2, 5, 8};
    m[4][7][1] = {0, 3, 6};
    m[4][7][3] = {1};

    m[4][8][0] = {1, 2, 5};
    m[4][8][1] = {3, 6, 7};
    m[4][8][3] = {0};

    m[5][0][0] = {3, 4, 6, 7, 8};
    m[5][0][1] = {1, 2};

    m[5][1][0] = {0, 3, 4, 6, 7, 8};
    m[5][1][1] = {2};

    m[5][2][0] = {0, 1, 3, 4, 6, 7};
    m[5][2][3] = {8};

    m[5][3][0] = {6, 7, 8};
    m[5][3][1] = {0, 1, 2};

    m[5][4][0] = {6, 7, 8};
    m[5][4][1] = {0, 1, 2};
    m[5][4][2] = {3};

    m[5][6][0] = {7, 8};
    m[5][6][1] = {0, 1, 2, 3, 4};

    m[5][7][0] = {8};
    m[5][7][1] = {0, 1, 2, 3, 4, 6};

    m[5][8][1] = {0, 1, 3, 4, 6, 7};
    m[5][8][3] = {2};

    m[6][0][1] = {1, 2, 4, 5, 7, 8};

    m[6][1][0] = {0, 3};
    m[6][1][1] = {2, 4, 5, 7, 8};

    m[6][2][0] = {0, 1, 3};
    m[6][2][1] = {5, 7, 8};

    m[6][3][1] = {1, 2, 4, 5, 7, 8};
    m[6][3][2] = {0};

    m[6][4][0] = {0, 1, 3};
    m[6][4][1] = {5, 7, 8};
    m[6][4][2] = {2};

    m[6][5][0] = {0, 1, 2, 3, 4};
    m[6][5][1] = {7, 8};

    m[6][7][0] = {0, 1, 2, 3, 4, 5};
    m[6][7][2] = {8};

    m[6][8][0] = {0, 1, 2, 3, 4, 5};

    m[7][0][0] = {3, 6};
    m[7][0][1] = {1, 2, 4, 5, 8};

    m[7][1][0] = {0, 3, 6};
    m[7][1][1] = {2, 5, 8};

    m[7][2][0] = {0, 1, 3, 4, 6};
    m[7][2][1] = {5, 8};

    m[7][3][0] = {6};
    m[7][3][1] = {0, 1, 2, 4, 5, 8};

    m[7][4][0] = {0, 3, 6};
    m[7][4][1] = {2, 5, 8};
    m[7][4][2] = {1};

    m[7][5][0] = {0, 1, 2, 3, 4, 6};
    m[7][5][1] = {8};

    m[7][6][1] = {0, 1, 2, 3, 4, 5};
    m[7][6][3] = {8};

    m[7][8][0] = {0, 1, 2, 3, 4, 5};
    m[7][8][3] = {6};

    m[8][0][0] = {3, 6, 7};
    m[8][0][1] = {1, 2, 5};

    m[8][1][0] = {0, 3, 4, 6, 7};
    m[8][1][1] = {2, 5};

    m[8][2][0] = {0, 1, 3, 4, 6, 7};

    m[8][3][0] = {6, 7};
    m[8][3][1] = {0, 1, 2, 4, 5};

    m[8][4][0] = {3, 6, 7};
    m[8][4][1] = {1, 2, 5};
    m[8][4][2] = {0};

    m[8][5][0] = {0, 1, 3, 4, 6, 7};
    m[8][5][2] = {2};

    m[8][6][1] = {0, 1, 2, 3, 4, 5};

    m[8][7][1] = {0, 1, 2, 3, 4, 5};
    m[8][7][2] = {6};

    memset(cancel, -1, sizeof(cancel));
    cancel[0][2] = 1;
    cancel[2][0] = 1;
    cancel[0][6] = 3;
    cancel[6][0] = 3;
    cancel[2][8] = 5;
    cancel[8][2] = 5;
    cancel[6][8] = 7;
    cancel[8][6] = 7;
    cancel[0][8] = 4;
    cancel[8][0] = 4;
    cancel[2][6] = 4;
    cancel[6][2] = 4;
    cancel[1][7] = 4;
    cancel[7][1] = 4;
    cancel[3][5] = 4;
    cancel[5][3] = 4;

    cin >> arr;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (i == j) continue;
            if (cancel[i][j] != -1) continue;

            // cout << i << " " << j << endl;
            rec(i, j, ((1 << 9) - 1) ^ (1 << i) ^ (1 << j));
        }
    }
    cout << ans << endl;

    return 0;
}
