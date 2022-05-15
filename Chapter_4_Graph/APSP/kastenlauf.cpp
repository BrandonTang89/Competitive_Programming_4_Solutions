/* Kattis - kastenlauf
Build graph using manhattan-distance. Perform floyd warshall transitive closure. Check from source to dest.

Time: O(V^3), Mem: O(V^2)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n_tc, n, x, y;
bool adjmat[109][109];
vector<tuple<int,int>> locs;
bool can_travel(int i, int j){
    auto [x1, y1] = locs[i];
    auto [x2, y2] = locs[j];
    return (abs(x1 - x2) + abs(y1 - y2) <= 1000);
}
int main(){
    fast_cin();
    cin >> n_tc;
    for (int tc=0;tc<n_tc;tc++){
        memset(adjmat, 0, sizeof(adjmat));
        locs.clear();

        cin >> n;
        n += 2;
        for (int i=0;i<n; i++){
            cin >> x >> y;
            locs.emplace_back(x, y);
        }

        for (int i=0;i<n;i++){
            for (int j=i;j<n;j++){
                adjmat[i][j] = adjmat[j][i] = can_travel(i, j);
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    adjmat[i][j] |= adjmat[i][k] & adjmat[k][j];
                }
            }
        }
        /*
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << adjmat[i][j] << " ";
            }
            cout << endl;
        }*/

        cout << (adjmat[0][n-1] ? "happy" : "sad") << endl;
    }


    return 0;
}