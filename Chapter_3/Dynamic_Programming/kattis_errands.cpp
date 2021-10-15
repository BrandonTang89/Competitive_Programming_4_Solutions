/* Kttis - errands
A seemingly easy shortest Hamiltonian path question is made a lot longer due to the need to map string locations to
their 2d grid locations and also the need to print the optimal route rather than just its length. 

This requires a conversion from location names to a vector of (x, y) points in a vector that can accessed 
according to the bitmask. Then after we find the shortest length possible, we need to trace it and store 
the order of locations visited in another vector that we convert backt into the original names.

Debugging:
    Remember to use EPS when comparing 2 (previously calculated) floating point numbers to prevent hard to diagnose
    errors.
    Also remember to flush input buffer before using getline after using cin.

Time: O(2^(n-1) * n^2) per test case
Mem: O(2^(n-1) * n)
*/ 
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long double ld;
#define LSOne(S) ((S) & -(S))
#define EPS 1e-12

int n;
ld x, y;
string name, tc;
map<string, pair<ld,ld>> locations;
ld memo[10 + 1 + 1][(int) (1<<(11-1))]; // 11 locations, including work, excluding home
vector<pair<ld,ld>> tcl; //test case locations
vector<int> order_visits;
vector<string> reverse_mapper;

ld dist(pair<ld,ld> a, pair<ld, ld> b){
    return (sqrt((a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second)));
}

ld dp(int u, int bm){
    if (bm == 0){
        return dist(locations["home"], tcl[u]);
    }
    ld &ans = memo[u][bm];
    if (ans != -1)return ans;
    ans = 1e9;

    int m = bm;
    while (m){
        int two_pow_v = LSOne(m);
        int v = __builtin_ctz(two_pow_v) + 1;
        ans = min(ans, dist(tcl[u], tcl[v]) + dp(v, bm^two_pow_v));
        m -= two_pow_v;
    }
    return ans;
}

void fill_order_visits(int u, int bm){
    //printf("u: %d, bm: %d\n", u, bm);
    if (bm == 0)return;
    int m = bm;
    while (m){
        int two_pow_v = LSOne(m);
        int v = __builtin_ctz(two_pow_v) + 1;
        m -= two_pow_v;
        if (abs(dp(u, bm) - (dist(tcl[u], tcl[v]) + dp(v, bm^two_pow_v))) <= EPS){ 
            // this node is next on the shortest path
            order_visits.emplace_back(v);
            fill_order_visits(v, bm^two_pow_v);
            break;
        }
    }
    return;
}

int main(){
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> name >> x >> y;
        locations[name] = make_pair(x,y);
    }

    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    while (getline(cin, tc)){
        // Reset Variables
        tcl.clear();
        order_visits.clear();
        reverse_mapper.clear();
        memset(memo, -1, sizeof(memo));

        // add in the work location as starting location
        tcl.emplace_back(locations["work"]);
        reverse_mapper.emplace_back("work");

        // Parse Input, split by char
        istringstream ss(tc);
        while (ss >> name){
            tcl.emplace_back(locations[name].first, locations[name].second);
            reverse_mapper.emplace_back(name);
        }
        n = (int) tcl.size();

        //for (auto i: tcl){printf("(%Le, %Le) ", i.first, i.second);}cout << endl;

        // Hamiltonian Path from work to home
        fill_order_visits(0, (1<<(n-1))-1);
        for (int i=0; i<(int)order_visits.size(); i++){
            cout << reverse_mapper[order_visits[i]] << ((i == (int) (order_visits.size() - 1)) ? '\n' : ' ');
        }

    }


   return 0;
}