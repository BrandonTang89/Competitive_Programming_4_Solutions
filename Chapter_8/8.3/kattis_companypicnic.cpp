/**Kattis - companypicnic
 * A kinda atypical DP question. its DP on a literal DAG, ie a rooted tree. State is the
 * current vertex, whether it has been taken or not. Transitions is to either pair the vertex
 * with one of its children or to just not pair it with anything.
 * 
 * Also, dont be dumb like me and spend 30+ mins debugging because I forgot that i did a n++
 * to account for CEO, thus i should only have n-1 edges remaining... Thus i was having
 * multiple additional edges, causing problems.
 * 
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
ld temp;
string parent, child;
vector<ld> speed;
map<string, int> m;
vector<int> adjlist[1001];

pair<int, ld> memo[1001][2];
pair<int, ld> dp(int p, bool taken) {  // returns maximum number of teams, max sum of speeds
    if (adjlist[p].size() == 0) return {0, 0};
    if (memo[p][taken].first != -1) return memo[p][taken];

    int teams = 0;
    ld sums = 0;
    for (auto c : adjlist[p]) {
        auto [c_teams, c_sums] = dp(c, false);  // don't take the child
        teams += c_teams;
        sums += c_sums;
    }
    pair<int, ld> best_pair = {teams, sums};

    if (!taken) {
        int cur_teams;
        ld cur_sums;
        for (auto &c : adjlist[p]) {                       // try taking this one
            auto [c_teams, c_sums] = dp(c, false);         // don't take the child
            auto [taken_teams, taken_sums] = dp(c, true);  // take the child
            cur_teams = teams - c_teams + 1 + taken_teams;
            cur_sums = sums - c_sums + min(speed[c], speed[p]) + taken_sums;

            // cout << "p " << p << " c " << c << endl;
            // cout << "cur_teams: " << cur_teams << " cur_sums: " << cur_sums << endl;

            best_pair = max(best_pair, {cur_teams, cur_sums});
        }
    }

    // cout << p << " " << taken << " " << best_pair.first << " " << best_pair.second << endl;

    return memo[p][taken] = best_pair;
}
int main() {
    cin >> n;
    n++;  // account for CEO
    speed.assign(n, 0);
    m.clear();

    for (int i = 0; i < n - 1; i++) {
        cin >> child >> temp >> parent;
        if (m.find(child) == m.end()) {
            m[child] = m.size();
        }
        if (m.find(parent) == m.end()) {
            m[parent] = m.size();
        }
        speed[m[child]] = temp;
        adjlist[m[parent]].emplace_back(m[child]);
    }

    /*
    for (auto u : m) {
        cout << u.first ;
        for (auto i: adjlist[u.second]){
            cout << " " << i ;
        }
        cout << endl;
    }*/
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            memo[i][j] = {-1, -1};
        }
    }

    pair<int, ld> ans = dp(m["CEO"], true);
    cout << setprecision(10) << fixed;
    cout << ans.first << " " << ans.second / (ld)ans.first << endl;
    return 0;
}