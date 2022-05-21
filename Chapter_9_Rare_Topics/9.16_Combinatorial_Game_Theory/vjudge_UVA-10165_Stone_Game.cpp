/**vjudge - UVA-10165
 * Direct application of nim sum idea, very classic.
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
    while (1) {
        cin >> n;
        if (n == 0) break;
        piles.resize(n);
        for (int i = 0; i < n; i++) cin >> piles[i];

        cout << (WinNimGame(piles) ? "Yes\n" : "No\n");
    }

    return 0;
}