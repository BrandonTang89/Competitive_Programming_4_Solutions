/**Kattis - cool1
 * slightly involved cycling finding problem. We start off by finding a cycle within the state-space
 * graph (row, col, instructionIndex). We do this by just keeping track of what states we've seen
 * before in a tuple set. But we need to obsereve that there may actually be smaller cycles of (row,
 * col) within the (row, col, instructionIndex) cycle. Thus, we go around the cycle and push all the
 * relevant (row, col) into a vector. We now need to find the minimum period of this vector.
 * Fortunately, the naive O(n^2) solution is fast enough for this (just trying periods of length
 * [1..n-1]).
 *
 * Time: O(less than n^6), Space: O(less than n^3). The time complexity is a bit hard to analyze
 * since we don't really have a good bound on the length of the state-space cycle, but we know that
 * it must be less than the size of the state space graph which is O(n^3).
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
map<tuple<int, int, int>, int> memo;
int curInstruction, cr, cc;
string instructions;
vector<vector<char>> grid;
int next()
{
    int moved = 0;
    if (instructions[curInstruction] == '^') {
        if (grid[cr - 1][cc] == '.') {
            cr--;
            assert(cr > 0);
            moved = 1;
        }
    }
    else if (instructions[curInstruction] == 'v') {
        if (grid[cr + 1][cc] == '.') {
            assert(cr < n - 1);
            cr++;
            moved = 1;
        }
    }
    else if (instructions[curInstruction] == '>') {
        if (grid[cr][cc + 1] == '.') {
            cc++;
            moved = 1;
        }
        assert(cc < n - 1);
    }
    else if (instructions[curInstruction] == '<') {
        if (grid[cr][cc - 1] == '.') {
            cc--;
            moved = 1;
        }
        assert(cc > 0);
    }
    else {
        assert(false);
    }
    curInstruction++;
    if (curInstruction == (int)instructions.size()) curInstruction = 0;
    return moved;
}
int main()
{
    fast_cin();
    cin >> n;
    curInstruction = 0;
    cin >> instructions;

    grid.assign(n, vector<char>(n, '.'));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'R') {
                cr = i;
                cc = j;
                grid[i][j] = '.';
            }
        }
    }

    memo[make_tuple(cr, cc, curInstruction)] = 1;  // seen this state before
    while (1) {
        int moved = next();

        if (memo.find(make_tuple(cr, cc, curInstruction)) != memo.end()) {
            vector<pair<int, int>> path;
            path.push_back(make_pair(cr, cc));
            int rootr = cr, rootc = cc, rooti = curInstruction;
            moved = next();
            while (cr != rootr || cc != rootc || curInstruction != rooti) {
                if (moved) path.push_back(make_pair(cr, cc));
                moved = next();
            }

            if (path.size() == 1) {
                cout << 1 << endl;
                return 0;
            }
            if (path.back() == path[0]) {
                path.pop_back();
            }

            for (int x = 1; x < (int)path.size() + 1; x++) {
                // check if path[0..x-1] is a period
                bool valid = true;
                for (int j = x; j < (int)path.size() && valid; j++) {
                    valid &= path[j] == path[j - x];
                }
                if (valid) {
                    cout << x << endl;
                    return 0;
                }
            }
            return 0;
        }
        if (moved != 0) {
            memo[make_tuple(cr, cc, curInstruction)] = 1;
        }
    }

    return 0;
}