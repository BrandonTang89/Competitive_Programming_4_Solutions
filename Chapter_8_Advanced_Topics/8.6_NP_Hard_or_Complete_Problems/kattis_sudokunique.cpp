/**Kattis - sudokunique
 * Relatively generic question about solving sudoku. Implementation is slightly tedious. We use the
 * heuristic that when doing substitutions, it is preferable to do the one with the least number of
 * options. Other than that, it is just brute force with not that much pruning.
 *
 * Time: O(?), Mem: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

bool duplicate;
string sol;

bool winning(string &board)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i * 9 + j] == '0') return false;
        }
    }
    return true;
}
bool validspecific(string &board, int i, int j)  // check if the board is valid at a specific cell
{
    assert(board[i * 9 + j] != '0');
    for (int k = 0; k < 9; k++) {
        if (k != j && board[i * 9 + k] == board[i * 9 + j]) return false;
        if (k != i && board[k * 9 + j] == board[i * 9 + j]) return false;
    }

    int bc = (i / 3) * 3;
    int br = (j / 3) * 3;
    for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 3; l++) {
            if (bc + k != i && br + l != j && board[(bc + k) * 9 + br + l] == board[i * 9 + j])
                return false;
        }
    }
    return true;
}

bool valid(string &board)
{  // check if the board is even valid
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i * 9 + j] == '0') continue;
            if (!validspecific(board, i, j)) return false;
        }
    }
    return true;
}

void recurse(string board)
{
    if (winning(board)) {
        if (sol == "") {
            sol = board;
            return;
        }
        else {
            duplicate = true;
            return;
        }
    }
    // we recurse to the place with the least number of options
    int mini = 10;
    int minx = -1;
    int miny = -1;
    string minoptions = "";

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i * 9 + j] != '0') continue;
            string options = "";
            for (int k = 1; k <= 9; k++) {
                board[i * 9 + j] = k + '0';
                if (validspecific(board, i, j)) {
                    options += k + '0';
                }
                board[i * 9 + j] = '0';
            }
            if ((int)options.length() < mini) {
                mini = options.length();
                minoptions = options;
                minx = i;
                miny = j;
            }
        }
    }
    if (mini == 0) return;
    assert(mini != 10);

    for (int i = 0; i < (int)minoptions.length(); i++) {
        board[minx * 9 + miny] = minoptions[i];
        recurse(board);
        if (duplicate) return;
        board[minx * 9 + miny] = '0';
    }
}
int main()
{
    string board;
    while (cin >> board) {
        string s;
        for (int i = 0; i < 80; i++) {
            cin >> s;
            board += s;
        }
        sol = "";
        if (!valid(board)) {
            cout << "Find another job" << endl << endl;
            continue;
        }

        duplicate = false;
        recurse(board);
        if (duplicate) {
            cout << "Non-unique" << endl << endl;
            continue;
        }
        if (sol == "") {
            cout << "Find another job" << endl << endl;
            continue;
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << sol[i * 9 + j] << " ";
            }
            cout << endl;
        }

        cout << endl;
    }

    return 0;
}