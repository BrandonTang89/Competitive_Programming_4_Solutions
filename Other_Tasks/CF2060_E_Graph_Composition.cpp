#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

int n, e, e2;
vector<vector<int>> adjlist;
vector<vector<int>> adjlistg;
vector<int> colour;

void dfs(int u, int col){
    colour[u] = col;
    for (int v : adjlistg[u]){
        if (colour[v] == -1){
            dfs(v, col);
        }
    }
}

vector<int> colour2;
void dfs2(int u, int col){
    colour2[u] = col;
    for (int v : adjlist[u]){
        if (colour2[v] == -1){
            dfs2(v, col);
        }
    }
}

int main(){
    int tc;
    cin >> tc;
    while(tc--){
        cin >> n >> e >> e2;
        adjlist.assign(n, vector<int>());
        adjlistg.assign(n, vector<int>());
        colour.assign(n, -1);

        vector<pair<int, int>> el(e);
        for (int i=0; i<e; i++){
            int a, b;
            cin >> a >> b;
            a--; b--;
            el[i] = {a, b};
        }

        for (int i=0; i<e2; i++){
            int a, b;
            cin >> a >> b;
            a--; b--;
            adjlistg[a].push_back(b);
            adjlistg[b].push_back(a);
        }


        // colour nodes based on G
        int col = 0;
        for (int i=0; i<n; i++){
            if (colour[i] == -1){
                dfs(i, col);
                col++;
            }
        }

        // remove edges across colours in F
        // vector<pair<int, int>> reducedel;
        int ans = 0;
        for (auto [a, b] : el){
            if (colour[a] == colour[b]){
                adjlist[a].push_back(b);
                adjlist[b].push_back(a);
            }
            else{
                ans++;
            }
        }

        // colour nodes based on F
        colour2.assign(n, -1);
        int col2 = 0;
        for (int i=0; i<n; i++){
            if (colour2[i] == -1){
                dfs2(i, col2);
                col2++;
            }
        }

        ans += col2 - col;
        cout << ans << endl;
    }

    return 0;
}