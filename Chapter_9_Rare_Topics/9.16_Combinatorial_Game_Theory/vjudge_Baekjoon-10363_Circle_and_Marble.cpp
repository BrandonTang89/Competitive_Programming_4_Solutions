/**vjudge - Baekjoon-10363 - Circle and Marble (same as LA 6803)
 * Interesting application of Sprague-Grundy theorem. Notice that the movements of the
 * individual marbles are independent of each other, so we can actually treat each marble
 * as an independant subgame where the state of each sub-game is just the position of
 * the marble, it is then very easy to calculate the grundy number for each position
 * of a marble. Okay but theres like 1,000,000*20,000 marbles? Well notice that we are
 * gonna XOR the grundy numbers anyway, if 2 marbles are in the same circle, their XOR
 * is actually gonna be 0, so actually XOR of the grundy numbers of n marbles in the same
 * circle is either 0 if n is even or just the grundy number of 1 marble! So we assume
 * each circle has x%2 marbles where x is the actual number of marbles.
 *
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

vector<vector<int>> children;
vector<int> piles, marbles;
int memo[20001];
int grundy(int u) {
    if (memo[u] != -1) return memo[u];
    if ((int)children[u].size() == 0) return 0;
    set<int> used;
    for (auto &v : children[u]) {
        used.insert(grundy(v));
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
int main() {
    int num_tc;
    cin >> num_tc;
    for (int tc = 1; tc <= num_tc; tc++) {
        memset(memo, -1, sizeof memo);
        cout << "Case #" << tc << ": ";
        int n;
        cin >> n;
        marbles.assign(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> marbles[i];
            marbles[i] %= 2;
        }
        children.assign(n, vi());
        for (int i = 0; i < n; i++) {
            int p;
            cin >> p;
            if (p == 0) continue;
            p--;
            children[p].emplace_back(i);
        }
        piles.clear();
        for (int i = 0; i < n; i++) {
            if (marbles[i]) piles.emplace_back(grundy(i));
        }
        cout << (WinNimGame(piles) ? "first\n" : "second\n");
    }

    return 0;
}