/* kattis - importspaghetti

50% of the problem is just dealing with the annoying input parsing.
The other 50% is finding the shortest cycle and printing it.

Notice that if we model each import as an edge with weight 1, the distance
from i to i is the shortest cycle begining and ending at i. From this, we can 
determine the length of the shortest cycle.

To actually print the shortest cycle, we use the parent matrix technique.

Time: O(V^3), Mem: O(V^2)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
const int INF = (int)1e9;

int n, n_lines, u, v, w;
string name, line, s;
map<string, int> m;
vector<string> fnames;
vector<int> cycle_path; 
vector<vector<int>> adjmat, p;
int main(){
    fast_cin();
    cin >> n;
    adjmat.assign(n, vector<int>(n, INF));
    cycle_path.clear();
    p.assign(n, vector<int>(n, -1)); // p[i][j] is the last node before j on path i -> j
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            p[i][j] = i;
        }
    }

    for (int i=0;i<n;i++){
        cin >> name;
        fnames.emplace_back(name);
        m[name] = i;
    }

    // input parsing...
    for (int i=0;i<n;i++){
        cin >> name >> n_lines;
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        for (int j=0;j<n_lines; j++){
            getline(cin, line);
            istringstream ss(line);
            ss >> name; // burn the "import" word

            while (ss >> name){
                if ((*--name.end()) == ','){
                    name.pop_back();
                }

                v = m[name];
                //printf("Edge %d -> %d\n", i, v);
                adjmat[i][v] = 1;
            }
            
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(adjmat[i][k] + adjmat[k][j] < adjmat[i][j]){
                    adjmat[i][j] = adjmat[i][k] + adjmat[k][j];
                    p[i][j] = p[k][j];

                }
            }
        }
    }

    int min_cycle_index=0, min_cycle_size = INF;
    for (int i=0;i<n;i++){
        if (adjmat[i][i] != INF){
            if (adjmat[i][i] < min_cycle_size){
                min_cycle_index = i;
                min_cycle_size = adjmat[i][i];
            }
        }
    }

    if (min_cycle_size == INF){
        cout << "SHIP IT" << endl;
        return 0;
    }

    int cur_node = p[min_cycle_index][min_cycle_index];
    while (cur_node != min_cycle_index){
        cycle_path.emplace_back(cur_node);
        cur_node = p[min_cycle_index][cur_node];
    }
    cycle_path.emplace_back(min_cycle_index);
    reverse(cycle_path.begin(), cycle_path.end());
    for(auto i: cycle_path){
        cout << fnames[i] << " ";
    }
    cout << endl;
    
}