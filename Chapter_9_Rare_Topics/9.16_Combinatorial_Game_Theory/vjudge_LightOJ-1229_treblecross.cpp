/**vjudge - lightOJ-1229 - TrebleCross. Same as UVA-10561
 * Application of Sprague-Grundy theorem
 * (https://cp-algorithms.com/game_theory/sprague-grundy-nim.html). First we start by seeing if the
 * game can be won in 1 move, if so then we need to put there to win.
 *
 * Else, notice that all blanks within 2 spaces from a cross are always not going to be put. So we
 * can actually just consider all the blanks that are not within 2 spaces of crosses. This allows
 * the game to be represented as a vector of numbers where each number represents a consecutive
 * segment of blanks that are at least 3 spaces away from a cross. We attempt to apply the
 * Sprague-Grundy theorem on these independent sub-games. Each possible move on a contiguous segment
 * of blanks essentially splits the segment into a left and right segment such that the 5 blanks
 * centered around the cross put are "deleted". This creates 2 more sub-games, one for each of the
 * two new segments. As such, to find the grundy number of each sub-game, we take the mex of the
 * set {grundy(left) XOR grundy(right) for all transitions}. This works because calling grundy
 * on left and right turns them into equivalent nim piles, and we can represent the composite
 * nim game as 1 pile with size of their XOR.
 *
 *
 * Once we have the grundy numbers, we apply the nimsum method to determine whether the state is
 * winnable rather trivially.
 *
 * To actually get the winning moves, we just try each blank and see is the new game is a losing
 * state.
 *
 * Time: O(n^2), Space: O(n^2) {notice the use of DP to compute the grundy numbers}
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int memo[203];
int grundy(int u) {
    if (u <= 0) return 0;
    if (memo[u] != -1) return memo[u];
    set<int> used;
    for (int i = 0; i < u; i++) {
        used.insert(grundy(i - 2) ^ grundy(u - 1 - i - 2));  // this is the important part
    }
    int res = 0;
    while (used.count(res)) res++;  // mex
    return memo[u] = res;
}

int getNimSum(vector<int> &piles) {
    int nim = 0;
    for (int i = 0; i < (int)piles.size(); i++) {
        nim ^= piles[i];
    }
    return nim;
}
bool WinNimGame(vector<int> &piles) {  // first player wins or not?
    int nim = getNimSum(piles);
    if (nim != 0) {
        return true;
    }
    return false;
}

vector<int> must_put;
int winnablestate(string s) {       // 0 is winnable in 1 move, 1 is winnable, 2 is losing
    vector<int> type(s.size(), 0);  // 1 is must put, 2 is cannot put, 0 is the remaining
    must_put.clear();
    for (int i = 0; i < (int)s.size(); i++) {
        // check for XX., X.X, .XX
        if (i >= 2 && s[i - 1] == 'X' && s[i - 2] == 'X') {
            type[i] = 1;
            continue;
        }
        if (i >= 1 && i <= (int)s.size() - 2 && s[i - 1] == 'X' && s[i + 1] == 'X') {
            type[i] = 1;
            continue;
        }
        if (i <= (int)s.size() - 3 && s[i + 1] == 'X' && s[i + 2] == 'X') {
            type[i] = 1;
            continue;
        }

        for (int j = max(0, i - 2); j <= min((int)s.size() - 1, i + 2); j++) {
            if (s[j] == 'X') {
                type[i] = 2;
                break;
            }
        }
    }

    // detect 1 move away from winning
    for (int i = 0; i < (int)s.size(); i++) {
        if (type[i] == 1) {
            must_put.push_back(i);
        }
    }
    if (must_put.size() != 0) {
        return 0;
    }

    // Split into piles and apply Sprague-Grundy theorem
    vector<int> piles;
    int cur = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (type[i] == 2 && cur != 0) {
            piles.push_back(grundy(cur));
            cur = 0;
        }
        if (type[i] == 0) {
            cur++;
        }
    }
    if (cur != 0) {
        piles.push_back(grundy(cur));
    }
    return WinNimGame(piles) ? 1 : 2;
}

int main() {
    int num_tc;
    memset(memo, -1, sizeof memo);
    cin >> num_tc;
    for (int i = 1; i <= num_tc; i++) {
        cout << "Case " << i << ": ";
        string s;
        cin >> s;

        if (winnablestate(s) == 0) {
            // cout << "WINNING" << endl;
            for (int i = 0; i < (int)must_put.size(); i++) {
                cout << must_put[i] + 1;
                if (i != (int)must_put.size() - 1) {
                    cout << " ";
                }
            }
        } else if (winnablestate(s) == 1) {
            vector<int> ans;
            // cout << "WINNING" << endl;
            for (int i = 0; i < (int)s.size(); i++) {
                if (s[i] == '.') {
                    string t = s;
                    t[i] = 'X';
                    if (winnablestate(t) == 2) {
                        ans.push_back(i);
                    }
                }
            }
            for (int i = 0; i < (int)ans.size(); i++) {
                cout << ans[i] + 1;
                if (i != (int)ans.size() - 1) {
                    cout << " ";
                }
            }
        } else {
            // cout << "LOSING" << endl;
            cout << 0;
        }
        cout << endl;
    }

    return 0;
}
