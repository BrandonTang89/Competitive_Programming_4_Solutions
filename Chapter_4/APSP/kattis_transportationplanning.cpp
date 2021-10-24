/* kattis - tranportationplanning
Another longish problem.
1. Build adjmat based on distances on the 2d grid
2. Do floyd warshall, dont need to worry about negative weights for this question.
3. For each unused edge (u -> v)
    Compute the total distance from i -> j for all 0 <= i < j < n
    dist(i, j) is the min of (i -> j), (i -> u -> v -> j), (i -> v -> u -> j)
4. Determine the best u -> v to use.

Debugging:
    Note that adjmat[u][u] = 0 is important here.
    Floating point comprisons, use double_equal

Time: O(V^4), Mem: O(V^2)
*/ 
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long double ld;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define EPS 1e-12
#define double_equal(a, b) (abs(a - b) <= EPS)

int n, e, x, y, u, v;
const ld INF = 1e9;
ld w;
vector<vector<ld>> adjmat, initial_adjmat;
vector<tuple<int,int>> cities;

ld dist(int u, int v){
    auto [x1, y1] = cities[u];
    auto [x2, y2] = cities[v];
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main(){
    fast_cin();
    cout.precision(std::numeric_limits<double>::digits10);
    while (true){
        cin >> n;
        cities.assign(n, make_tuple(0, 0));
        adjmat.assign(n, vector<ld>(n, INF));

        if (n == 0)break;
        for(int i=0;i<n;i++){
            cin >> x >> y;
            cities[i] = make_tuple(x, y);
        }

        cin >> e;
        for (int i=0;i<e;i++){
            cin >> u >> v;
            adjmat[u][v] = adjmat[v][u] = dist(u, v);
        }

        initial_adjmat = adjmat;
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
                }
            }
        }


        ld init = 0;
        for (int u=0;u<n;u++){
            for (int v=0; v<u;v++){
                //cout << "u : " << u << " v: " << v << " adjmat[u][v]: " << adjmat[u][v] << endl;
                init += adjmat[u][v];
            }
        }

        for (int i=0;i<n;i++){
            adjmat[i][i] = 0;
        }
        int best_u = -1, best_v = -1;
        ld min_tot = init;
        // for each unused edge (note the order of u,v to be inline with task requirements)
        for (int u=0;u<n;u++){
            for (int v=u; v<n;v++){
                if (double_equal(initial_adjmat[u][v], INF)){
                    // compute the total distance
                    ld cur = 0;
                    w = dist(u, v);
                    for (int i=0;i<n;i++){
                        for (int j=0; j<i;j++){
                            ld l_dist = min(adjmat[i][j], adjmat[i][u] + w + adjmat[v][j]);
                            l_dist = min(l_dist, adjmat[i][v] + w + adjmat[u][j]);

                            //printf("u: %d, v:%d, i: %d, j: %d, l_dist: %Le\n", u, v, i, j, l_dist);
                            cur += l_dist;
                        }
                    }

                    if (cur < min_tot){
                        min_tot = cur; 
                        best_u = u;
                        best_v = v;
                    }

                    //printf("u: %d, v:%d, cur:%Le\n", u, v, cur);
                }
            }
        }

        if (double_equal(min_tot, init)){
            cout << "no addition reduces " << init << endl; 
        }
        else{
            cout << "adding " << best_u << " " << best_v << " reduces " << init << " to " << min_tot << endl;
        }


    }


    return 0;
}