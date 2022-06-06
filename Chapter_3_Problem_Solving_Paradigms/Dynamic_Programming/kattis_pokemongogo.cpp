/**Kattis - pokemongo
 * Minimimum Hamiltonian tour variant. Here we need to visit each unique pokemon once and only once but they can
 * exist at different locations, so we just try all of those locations whenever we opt to visit a specific
 * pokemon next.
 * 
 * Note that in my code I offset all the locations but this is not needed.
 * Time: O(num_positions^2 * 2^num_unique_pokemon), Space: O(num_positions* 2^num_unique_pokemon)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define MAX_n 16
int num_stops, n;  // n is then no. unique pokemon
map<string, int> pokemon;
vector<vector<int>> locs;    // locs[pokemon_index] = {(r, c), (r, c), ...}
vector<pair<int, int>> pos;  // record the positions

#define LSOne(S) ((S) & -(S))
int memo[21][1 << MAX_n];

int dist(int r1, int c1, int r2, int c2) { return abs(r1 - r2) + abs(c1 - c2); }
int dp(int u, int mask) {  // mask = free pokemon
    int &ans = memo[u][mask];
    if (ans != -1) return ans;  // computed before
    int r = pos[u].first, c = pos[u].second;
    if (mask == 0) return ans = dist(r, c, 100, 100);  // close the loop
    ans = 2000000000;                                  // INF
    int m = mask;
    while (m) {                            // up to O(n)
        int two_pow_v = LSOne(m);          // but this is fast
        int v = __builtin_ctz(two_pow_v);  // offset v by +1
        for (auto p : locs[v]) {
            ans = min(ans, dist(r, c, pos[p].first, pos[p].second) + dp(p, mask ^ two_pow_v));
        }
        m -= two_pow_v;
    }
    return ans;
}

int main() {
    cin >> num_stops;
    for (int i = 0; i < num_stops; i++) {
        string name;
        int r, c;
        cin >> r >> c;
        cin >> name;
        if (pokemon.count(name) == 0) {
            pokemon[name] = n++;
            locs.push_back({});
        }
        locs[pokemon[name]].push_back(i);
        pos.push_back({r + 100, c + 100});
    }
    pos.push_back({100, 100});

    memset(memo, -1, sizeof(memo));
    int shortest_H_cycle = dp(pos.size() - 1, (1 << n) - 1);
    cout << shortest_H_cycle << endl;
    return 0;
}