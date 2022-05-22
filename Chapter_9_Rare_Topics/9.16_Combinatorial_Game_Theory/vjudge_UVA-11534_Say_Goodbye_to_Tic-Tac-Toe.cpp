/**vjudge - UVA-11534 - Say Goodbye to tic tac toe
 * Tedious application of Sprague-Grundy theorem. First is to model the 1 by n board as
 * a 2 by n board where putting a cross at position i puts a ⊥ on the board centered
 * at i, putting a circle puts ⊤ on the board centered at i (or vice versa).
 *
 * So after we do some moves, we have the board split into several independent sub-games.
 * Since pices are only of radius 1, they cannot possibly bridge over any gaps between
 * the sub-games. So we should try to apply the Sprague-Grundy theorem, finding the
 * grundy numbers for each sub-game.
 *
 * The problem is the sub-games are annoying to model. One way is to use the state
 * representation (l1, r1, l2, r2) since the top and the bottom of each sub-game is
 * in 1 contiguous row.  The problem is that this leads to O(n^4) states, and
 * with O(n) transition, it might TLE. The more tedious but more efficient way is
 * to notice that there are only 4 families of sub-games.
 *
 * 1. both equal length and aligned
 * 2. both alinged to 1 side, differ in length by 1
 * 3. both equal length, misaligned by 1
 * 4. lengths differ by 2, misaligned by 1 on both sides
 *
 * If we know the type of sub-game, we only need to know the length of the shorter side
 * of the sub-game piece to actually build back to the l1,r1,l2,r2 representation. So thats what we
 * do.. write code to convert between the l1,r1,l2,r2 representation and the (type, length)
 * representation. This allows us to efficiently calculate the grundy numbers for each sub-game.
 * then we just use the Nim Sum as per usual.
 *
 * Note the prety elegant method to parse the string and generate the required sub-games.
 *
 * Also note that whether we need to detect whether to find losing or winning state depending
 * on whose turn it is, which depends on the number of crosses + circles already on the board.
 * 
 * Time: O(n^2), Space: O(n)
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

int memo[4][101];
int grundy_wrapper(int l1, int r1, int l2, int r2);
int grundy(int type, int len) {  // type, length
    if (memo[type][len] != -1) return memo[type][len];
    // Expand type and l into proper blocks
    assert(len > 0);
    int l1, r1, l2, r2;  // block 1 is the shorter / more left block
    if (type == 0) {
        l1 = l2 = 0;
        r1 = r2 = len - 1;
    } else if (type == 1) {
        l1 = l2 = 0;
        r1 = len - 1;
        r2 = len;
    } else if (type == 2) {
        if (len == 1) return 0;
        l1 = 0;
        r1 = 1;
        l2 = len - 1;
        r2 = len;
    } else if (type == 3) {  // block 1 is the bigger block
        l1 = 0;
        r1 = len + 1;
        l2 = 1;
        r2 = len;
    } else
        assert(false);

    set<int> used;
    for (int i = l1; i <= r1; i++) {
        used.insert(grundy_wrapper(l1, i - 2, l2, i - 1) ^ grundy_wrapper(i + 2, r1, i + 1, r2));
    }
    for (int i = l2; i <= r2; i++) {
        used.insert(grundy_wrapper(l1, i - 1, l2, i - 2) ^ grundy_wrapper(i + 1, r1, i + 2, r2));
    }

    int res = 0;
    while (used.count(res)) res++;  // mex
    return memo[type][len] = res;
}

int grundy_wrapper(int l1, int r1, int l2, int r2) {
    // cout << "l1: " << l1 << " r1: " << r1 << " l2: " << l2 << " r2: " << r2 << endl;
    if (l1 > r1 && l2 > r2) return 0;
    if (l1 > r1) return 1;
    if (l2 > r2) return 1;
    // Check which of the cases it is...
    if (l1 == l2 && r1 == r2) return grundy(0, r1 - l1 + 1);
    if (l1 == l2) return grundy(1, min(r1, r2) - l1 + 1);
    if (r1 == r2) return grundy(1, r1 - max(l1, l2) + 1);
    if (r1 - l1 == r2 - l2) return grundy(2, r2 - l2 + 1);

    assert(abs(r2 - l2 - (r1 - l1)) == 2);  // difference of 2
    return grundy(3, min(r2 - l2, r1 - l1) + 1);
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
    memset(memo, -1, sizeof(memo));
    int num_tc;
    cin >> num_tc;
    vector<int> piles;
    for (int tc = 0; tc < num_tc; tc++) {
        piles.clear();
        string s;
        cin >> s;
        int l1 = 0, r1 = s.size() - 1, l2 = 0, r2 = s.size() - 1;

        int pieces = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == 'X') {
                piles.emplace_back(grundy_wrapper(l1, i - 2, l2, i - 1));
                l1 = i + 2;
                l2 = i + 1;
                pieces++;
            } else if (s[i] == 'O') {
                piles.emplace_back(grundy_wrapper(l1, i - 1, l2, i - 2));
                l1 = i + 1;
                l2 = i + 2;
                pieces++;
            }
        }
        piles.emplace_back(grundy_wrapper(l1, r1, l2, r2));

        if (pieces % 2 == 0 && WinNimGame(piles)) {
            cout << "Possible." << endl;
        } else if (pieces % 2 == 1 && !WinNimGame(piles)) {
            cout << "Possible." << endl;
        } else {
            cout << "Impossible." << endl;
        }
    }

    return 0;
}