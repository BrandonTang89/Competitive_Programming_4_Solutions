/* Kattis - arbitrage
A Floyd Warshall Modification. use multiply instead of add, and we are finding the max rather
than the min. Note that we need to do detection of a found solution within the Floyd Warshall to
prevent TLE from the high cost of O(V^3)...

Time: O(V^3), Mem: O(V^2)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long double ld;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, e, u, v;
ld w; 
string c1, c2, rate;
vector<vector<ld>> adjmat;
map<string, int> m;
int main(){
    fast_cin();
    while (1){
        cin >> n;
        if (n == 0)break;
        adjmat.assign(n, vector<ld>(n, 0));
        for (int i=0;i<n;i++){
            cin >> c1;
            m[c1] = i;
            adjmat[i][i] = (ld) 1;
        }
        cin >> e;
        for (int i=0;i<e;i++){
            cin >> c1 >> c2 >> rate;
            
            int x1 = stoi(rate.substr(0, rate.find(':')));
            rate.erase(0, rate.find(':') + 1);
            int x2 = stoi(rate.substr(0, rate.find(':')));

            w = (ld) x2/ (ld) x1;
            adjmat[m[c1]][m[c2]] = w;
        }
        
        bool arbitrage = false;
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    adjmat[i][j] = max(adjmat[i][j], adjmat[i][k] * adjmat[k][j]);
                    if (i == j && adjmat[i][j] > 1){
                        arbitrage = true;
                        break;
                    }
                }
                if (arbitrage)
                    break;
            }
            if (arbitrage)
                break;
        }

        cout << (arbitrage ? "Arbitrage" : "Ok") << endl;

    }

    return 0;
}