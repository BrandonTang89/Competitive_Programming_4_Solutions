/**Kattis - socialadvertising
 * Textbook minimum dominating set problem. Use DP. 
 * 
 * Time: O(2^n). Space: O(2* 2^n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
vector<int> adjmat; // bitmask adjmat[i] & (1 << j) == 1 iff there is an edge from i to j
int INF = 1e9;
const int MAX_N = 20;

int memo[MAX_N][(1 << MAX_N)];
int minimum_set_cover(int idx, int mask){ // search for minimum set cover
    if (idx == n)return (mask == ((1 << n) - 1) ? 0 : INF);
    if (memo[idx][mask] != -1)return memo[idx][mask];
    return memo[idx][mask] = min(minimum_set_cover(idx + 1, mask), 1 + minimum_set_cover(idx + 1, mask | adjmat[idx]));
}

int main(){
    int num_tc;
    cin >> num_tc;
    for (int tc=0; tc<num_tc; tc++){
        cin >> n;
        adjmat.assign(n, 0);
        memset(memo, -1, sizeof memo);
        for (int i=0; i<n; i++){
            adjmat[i] |= (1 << i);
        }
        for (int u=0; u<n; u++){
            int k; // num neighbours
            cin >> k;
            for (int i=0; i<k; i++){
                int v;
                cin >> v;
                adjmat[u] |= (1 << (v-1));
            }
        }
        cout << minimum_set_cover(0, 0) << endl;
    }

    return 0;
}