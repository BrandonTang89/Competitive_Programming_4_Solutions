/**vjudge - UVA-1566
 * Classic Misere Nim game, follow the theory and it'll be easy.
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
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

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

bool WinMisereNimGame(vector<int> &piles) {
    int n_mt1 = 0, n_one = 0;
    for (int i = 0; i < (int)piles.size(); i++) {
        if (piles[i] == 1)
            n_one++;
        else
            n_mt1++;
    }
    if (n_mt1 >= 1) {
        // force opponent to move to 1 pile with >1 stones, then adjust that to 0 or 1
        return WinNimGame(piles);
    } else {
        return (n_one % 2 == 0);
    }
}

int n;
vector<int> piles;
int main() {
    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        cin >> n;
        piles.resize(n);
        for (int i = 0; i < n; i++) cin >> piles[i];

        cout << (WinMisereNimGame(piles) ? "John\n" : "Brother\n");
    }

    return 0;
}