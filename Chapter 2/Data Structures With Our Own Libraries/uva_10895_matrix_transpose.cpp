// UVA 10895 Matrix Transpose
// Transpose a matrix given in the form of an adjlist, pretty basic but could be confusing
// Time O(RC)
#include <bits/stdc++.h>
using namespace std;

int n, u, v, w;
int r,c;
vector<pair<int,int>> adjlist1[10009];
vector<pair<int,int>> adjlist2[10009];

int main(){
    while (cin >> r){
        cin >> c;

        for (int u=0; u<r; u++){
            cin >> n;
            vector<int> v_list;

            for (int i=0;i<n;i++){
                cin >> v;
                v--;
                v_list.push_back(v);
            }
            for(int i=0;i<n;i++){
                cin >> w;
                adjlist1[u].push_back(make_pair(v_list[i], w));
            }
        }

        // transpose;
        for (int u=0;u<r; u++){
            for (auto k: adjlist1[u]){
                v = k.first; w=k.second;
                adjlist2[v].push_back(make_pair(u, w));
            }
        }

        // print output
        cout << c << " " << r << endl;
        for (int u=0; u<c;u++){
            cout << adjlist2[u].size();
            if (adjlist2[u].size() > 0) cout << " ";
            
            for (vector<pair<int,int>>::iterator it = adjlist2[u].begin(); it!= adjlist2[u].end(); it++ ){
                cout << (*it).first+1;
                if (it +1 != adjlist2[u].end()) cout << " ";
            }
            cout << endl;
            for (vector<pair<int,int>>::iterator it = adjlist2[u].begin(); it!= adjlist2[u].end(); it++ ){
                cout << (*it).second;
                if (it +1 != adjlist2[u].end()) cout << " ";
            }
            cout << endl;
        }

        for (int i=0;i<10009;i++){
            adjlist1[i].clear();
            adjlist2[i].clear();
        }
    }
    

    return 0;
}