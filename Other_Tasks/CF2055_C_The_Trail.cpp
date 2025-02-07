#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;

int h, w;
vector<vector<ll>> grid;
int main(){
    int tc;
    cin >> tc;
    while(tc--){
        cin >> h >> w;
        grid.assign(h, vector<ll>(w, 0));
        vector<ll> rowSum(h, 0);
        vector<ll> colSum(w, 0);

        vector<char> path(w + h-1, '_'); // dummy char in the end
        for (int i = 0; i< w + h - 2; i++){
            cin >> path[i];
        }

        for (int i = 0; i < h; i++){
            for (int j = 0; j < w; j++){
                cin >> grid[i][j];
                rowSum[i] += grid[i][j];
                colSum[j] += grid[i][j];
            }
        }

        int r = 0;
        int c = 0;
        int idx = 0;

        while (idx < w + h - 1){
            assert(r < h && c < w);
            if (path[idx] == 'R'){ // we just care about the column
                ll v = -colSum[c];
                colSum[c] = 0;
                rowSum[r] += v;

                grid[r][c] = v;
                c++;
            }
            else{
                ll v = -rowSum[r];
                rowSum[r] = 0;
                colSum[c] += v;

                grid[r][c] = v;
                r++;
            }
            idx++;
            
        }

        for (int i = 0; i < h; i++){
            for (int j = 0; j < w; j++){
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }

    }

    return 0;
}