/**Kattis - crosscountry
 * SSSP on a small graph, we can reduce the code length by just doing Floyd-Warshall.
 * 
 * Time: O(V^3), Mem: O(V^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, src, dest;
int adjmat[1001][1001];
int main(){
    fast_cin();
    cin >> n >> src >> dest;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> adjmat[i][j];
        }
    }

    for (int k=0; k<n; k++){
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                adjmat[i][j] = min(adjmat[i][j], (adjmat[i][k] + adjmat[k][j]));
            }
        }
    }

    cout << adjmat[src][dest] << endl;

    return 0;
}