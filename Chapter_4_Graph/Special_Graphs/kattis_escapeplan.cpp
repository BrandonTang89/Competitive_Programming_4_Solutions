/* Kattis - escapeplan
Decently easy MCBM problem. Quite obvious that we need to match the robots to the holes. Just a 
moderate amount of extra processing to do to set up the graph. Do it systematically and it'll
be okay.

Note that its not a good (fast) idea to mix c and c++ style IO. But i mean, speed isn't of the
essence for this question.

Time: O(VE), Space: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long double ld;
#define EPS 1e-9

ld dist(pair<ld, ld> a, pair<ld, ld> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

bool can_make_it(int time, pair<ld,ld> a, pair<ld,ld>b){
    return (dist(a, b) - ((ld) time*10) < EPS);
}

vector<pair<ld, ld>> robots, holes;
vector<vector<int>> adjlist;
vector<int> match, visited;
int n_r, n_h, times[] = {5, 10, 20};
ld x, y;

// MCBM Augmenting Path Algorithm
int aug(int L){
    if (visited[L]) return 0;
    visited[L] = 1;
    for (auto &R : adjlist[L]){
        if (match[R] == -1 || aug(match[R])){
            match[R] = L;
            return 1;
        }
    }
    return 0;
}

int main(){
    for (int num_tc = 1;; num_tc++){
        cin >> n_r;
        robots.clear();
        holes.clear();
        if (n_r == 0) break;
        printf("Scenario %d\n", num_tc);
        for (int i=0; i<n_r; i++){
            cin >> x >> y;
            robots.push_back({x, y});
        }
        cin >> n_h;
        for (int i=0; i<n_h; i++){
            cin >> x >> y;
            holes.push_back({x, y});
        }
        for (auto time: times){
            adjlist.assign(n_r + n_h, vector<int>());
            match.assign(n_r + n_h, -1);
            for (int i=0; i<n_r; i++){
                for (int j=0; j<n_h; j++){
                    if (can_make_it(time, robots[i], holes[j])){
                        adjlist[i].push_back(n_r + j);
                        adjlist[n_r + j].push_back(i);
                    }
                }
            }

            int MCBM = 0;
            for (int i=0; i<n_r; i++){
                visited.assign(n_r + n_h, 0);
                MCBM += aug(i);
            }

            printf("In %d seconds %d robot(s) can escape\n", time, MCBM);
        }
        printf("\n");
    }

    return 0;
}