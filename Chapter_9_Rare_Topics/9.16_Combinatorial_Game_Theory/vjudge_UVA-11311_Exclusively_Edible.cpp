/**vjudge - UVA-11311
 * Nim game modelling. Let there be four piles such that they represent the number of 
 * cells to the left,up, down, and right of the bad part. Notice that each cut will
 * take a non-zero amount from only 1 pile. Then the loser is the one who has no more
 * from any pile to take. This is basically nim.
 * 
 * Time: O(1), Space: O(1)
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

int getNimSum(vector<int> &piles) {
    int nim = 0;
    for (int i = 0; i < (int) piles.size(); i++) {
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

int n;
vector<int> piles;
int main() {
    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        int h, w, r, c;
        cin >> h >> w >> r >> c;
        piles = {h-r-1, w-c-1, r, c};
        cout << (WinNimGame(piles) ? "Gretel\n" : "Hansel\n");
    }

    return 0;
}