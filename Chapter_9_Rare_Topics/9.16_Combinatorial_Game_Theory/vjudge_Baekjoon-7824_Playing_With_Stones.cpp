/**vjudge - Baekjoon-7824 - Playing With Stones (Same as LA-5059)
 * Application of Sprague-Grundy theorem. Decently easy, but beware of integer overflow.
 * 
 * We generate a few (first 16) grundy numbers then notice that if n is even, g(n) = n/2
 * and else g(n) = g((n-1)/2). So now we can compute g(n) in O(log n) time, sufficiently
 * fast.
 * 
 * Then just directly apply the theorem and use nim-sum to get the answer.
 *
 * Time: O(n log A), Space: O(n) where A is the size of the pile
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

ll grundy(ll u) {
    if (u == 1 || u == 0) return 0;
    if (u%2 == 0) return u/2LL;

    return grundy((u-1)/2LL);
}

ll getNimSum(vector<ll> &piles) {
    ll nim = 0;
    for (int i = 0; i < (int)piles.size(); i++) {
        nim ^= piles[i];
    }
    return nim;
}
bool WinNimGame(vector<ll> &piles) {  // first player wins or not?
    ll nim = getNimSum(piles);
    if (nim != 0) {
        return true;
    }
    return false;
}


int main() {
    int num_tc;
    cin >> num_tc;
    vector<ll> piles;
    for (int i = 1; i <= num_tc; i++) {
        int n;
        cin >> n;
        piles.resize(n);
        for (int j = 0; j < n; j++){
            cin >> piles[j];
            piles[j] = grundy(piles[j]);
        }
        cout << (WinNimGame(piles) ? "YES\n" : "NO\n");
    }

    return 0;
}