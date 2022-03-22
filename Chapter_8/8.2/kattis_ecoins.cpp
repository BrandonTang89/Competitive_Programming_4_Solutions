/**Kattis - ecoins
 * This is a straightforward state space search problem. So just like with regular coin change,
 * we are trying to find the minimum number of ecoins to use. We model each (sum of conventional,
 * sum of IT val) as a vertex. Then each coin represents a transition. Note that we use a hashmap
 * to store distance from source. We need to use the custom pair_hash struct as C++ doesn't
 * natively support hashmaps with pairs as keys. Using a bst of pairs is too slow. 
 * 
 * Time: O(dest^2), Space: O(dest^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int num_tc;
int n, dest, conv, itv;
vector<pair<int, int>> coins;
queue<pair<int, int>> q;
struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int>& v) const {
        std::size_t seed = 0;
        seed ^= v.first + 0x9e3779b9 + (seed<<6) + (seed>>2);
        seed ^= v.second + 0x9e3779b9 + (seed<<6) + (seed>>2);
        return seed;
    }
};
unordered_map<pair<int, int>, int, pair_hash> dist;
int main() {
    fast_cin();
    cin >> num_tc;
    for (int tc = 0; tc < num_tc; tc++) {
        cin >> n >> dest;
        coins.resize(n);
        dest *= dest;
        for (int i = 0; i < n; i++) {
            cin >> conv >> itv;
            coins[i] = make_pair(conv, itv);
        }

        // we BFS from 0 to dest
        bool done = false;
        while (!q.empty()) q.pop();
        dist.clear();

        dist[make_pair(0, 0)] = 0;
        q.push(make_pair(0, 0));
        while (!q.empty()) {
            auto cur = q.front();
            conv = cur.first;
            itv = cur.second;
            q.pop();

            for (int i = 0; i < n; i++) {
                int new_conv = conv + coins[i].first;
                int new_itv = itv + coins[i].second;
                int new_val = new_conv * new_conv + new_itv * new_itv;
                if (new_val > dest) continue;

                if (new_val == dest){
                    cout << dist[cur] + 1 << endl;
                    done = true;
                    break;
                }

                if (dist.find(make_pair(new_conv, new_itv)) == dist.end()) {
                    dist[make_pair(new_conv, new_itv)] = dist[cur] + 1;
                    q.push(make_pair(new_conv, new_itv));
                }
            }
            
            if (done) break;
        }

        if (!done){
            cout << "not possible" << endl;
        }
    }
    return 0;
}