#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


int main(){
    int tc;
    cin >> tc;
    while (tc--){
        int n, st, en;
        cin >> n >> st >> en;
        st--, en--;
        vector<vector<int>> adjlist(n, vector<int>());
        for (int i=0; i<n-1; i++){
            int u, v;
            cin >> u >> v;
            u--, v--;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }
        
        // we first find the shortest path from S to E
        vector<int> dist(n, -1);
        queue<int> q;
        q.push(st);
        dist[st] = 0;
        while (!q.empty()){
            int u = q.front();
            q.pop();
            for (int v : adjlist[u]){
                if (dist[v] == -1){
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        vector<int> path;
        path.push_back(en);
        int cur = en;
        while (cur != st){
            for (int v : adjlist[cur]){
                if (dist[v] == dist[cur] - 1){
                    path.push_back(v);
                    cur = v;
                    break;
                }
            }
        }
        reverse(path.begin(), path.end());
        unordered_set<int> path_set(path.begin(), path.end());
        

        // now we traverse along the path, exploring the surrounding sub trees first before going down the path
        vector<int> ans;
        dist.assign(n, -1);
        vector<pair<int, int>> subtree; // dist, node
        int pathLen = path.size();
        for (int i=0; i<pathLen; i++){
            int root = path[i];
            dist[root] = 0;
            for (int v : adjlist[root]){
                if (path_set.find(v) == path_set.end()){
                    q.push(v);
                    dist[v] = 1;
                }
            }

            while (!q.empty()){
                int u = q.front();
                subtree.push_back({dist[u], u});
                q.pop();
                for (int v : adjlist[u]){
                    if (dist[v] == -1){
                        dist[v] = dist[u] + 1;
                        q.push(v);

                    }
                }
            }

            for (auto it = subtree.rbegin(); it != subtree.rend(); it++){
                ans.push_back(it->second + 1);
            }

            subtree.clear();
            ans.push_back(root + 1);
        }

        for (auto x: ans){
            cout << x << " ";
        }
        cout << endl;

    }



    return 0;
}