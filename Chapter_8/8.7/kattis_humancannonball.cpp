/**Kattis - humancannonball
 * easy in theory, abit tedious in practise. We do Floyd-Warshall on all the cannons to determine
 * the fastest time to get between any 2 cannons. Then we do a n^2 check to go from A to
 * cannon i to cannon j to B. Note that between any 2 locations, we can always either run or
 * use the cannon (assuming we start from a cannon). Especially from j to B, we need to check
 * if taking the cannon is faster.
 * 
 * Time: O(n^3), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
pair<ld, ld> source, dest;
vector<vector<ld>> adjmat;
vector<pair<ld, ld>> cannons;
int main(){
    ld x, y;
    cin >> x >> y;
    source = {x, y};
    cin >> x >> y;
    dest = {x, y};

    cin >> n;
    adjmat.assign(n, vector<ld>(n, INT_MAX));
    cannons.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> cannons[i].first >> cannons[i].second;
        adjmat[i][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ld d = sqrt(pow(cannons[i].first - cannons[j].first, 2) + pow(cannons[i].second - cannons[j].second, 2));
            adjmat[i][j] = adjmat[j][i] = d/5.0;

            ld running_d;
            if (d > 50){
                running_d = d - 50;
            }
            else{
                running_d = 50 - d;
            }
            adjmat[i][j] = min(adjmat[i][j], 2 + running_d/5.0);
            adjmat[j][i] = min(adjmat[j][i], 2 + running_d/5.0);
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
            }
        }
    }

    ld ans = sqrt(pow(source.first - dest.first, 2) + pow(source.second - dest.second, 2))/5.0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            ld source_to_i = sqrt(pow(source.first - cannons[i].first, 2) + pow(source.second - cannons[i].second, 2))/5.0;
            ld j_to_dest_dist = sqrt(pow(cannons[j].first - dest.first, 2) + pow(cannons[j].second - dest.second, 2));
            ld j_to_dest_time = j_to_dest_dist/5.0;

            ld running_d = abs(50 - j_to_dest_dist);
            j_to_dest_time = min(j_to_dest_time, 2 + running_d/5.0);
            ans = min(ans, source_to_i + adjmat[i][j] + j_to_dest_time);

            // cout << "i: " << i << " j: " << j << " cur: " << adjmat[i][j] << endl;
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
    return 0;
}