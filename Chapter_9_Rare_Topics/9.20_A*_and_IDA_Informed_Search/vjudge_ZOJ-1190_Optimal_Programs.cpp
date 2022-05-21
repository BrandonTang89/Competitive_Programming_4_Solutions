/**vjudge - ZOJ-1190 (same as UVA-656) - optimal programs
 * Iterative Deepening Depth First Search. We try longer and longer
 *
 * Time: O(?), Space: O(num_cells)
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

string opnames[] = {"ADD", "DIV", "DUP", "MUL", "SUB"};

vector<vector<int>> stacks;
vector<int> outputs;
vector<int> moves(11);
int limit, n;
bool dfs(int g) {
    if (g > limit) return false;
    bool done = true;
    for (int i = 0; i < n; i++) {
        if (stacks[i].size() != 1 || stacks[i].back() != outputs[i]) {
            done = false;
        }
        if (abs(stacks[i].back()) > 30000) return false; // overflow -- check this
    }
    if (done) return true;

    int a, b;
    vector<vector<int>> backup = stacks;
    bool top_zero = false;
    for (int i = 0; i < n; i++) {
        if (stacks[i].back() == 0) {
            top_zero = true;
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (i != 2) {
            if ((int)stacks[0].size() == 1) continue;  // not enough elements
            if (i == 1 && top_zero) continue;          // we can't do division
            for (int j = 0; j < n; j++) {
                a = stacks[j].back();
                stacks[j].pop_back();
                b = stacks[j].back();
                stacks[j].pop_back();

                if (i == 0) {
                    stacks[j].push_back(b + a);
                } else if (i == 1) {
                    stacks[j].push_back(b / a);
                } else if (i == 3) {
                    stacks[j].push_back(b * a);
                } else if (i == 4) {
                    stacks[j].push_back(b - a);
                }
            }
        } else {
            for (int j = 0; j < n; j++) {
                stacks[j].push_back(stacks[j].back());
            }
        }
        moves[g] = i;
        if (dfs(g + 1)) return true;
        stacks = backup;
    }

    return false;
}

int iddfs() {
    for (limit = 0; limit <= 10; limit++) {
        if (dfs(0)) return limit;
    }
    return -1;
}

int main() {
    fast_cin();
    for (int program_cnt = 1;; program_cnt++) {
        cin >> n;
        if (n == 0) break;
        stacks.assign(n, vector<int>());
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            stacks[i].push_back(x);
        }
        outputs.assign(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> outputs[i];
        }

        int ans = iddfs();
        cout << "Program " << program_cnt << "\n";
        if (ans == -1) {
            cout << "Impossible" << endl;
        } else if (ans == 0) {
            cout << "Empty sequence" << endl;
        } else {
            for (int i = 0; i < ans; i++) {
                cout << opnames[moves[i]];
                if (i != ans - 1) cout << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}