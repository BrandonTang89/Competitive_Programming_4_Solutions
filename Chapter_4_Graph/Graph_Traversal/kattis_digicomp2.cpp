/**Kattis - digicomp2
 * Observe that we should process the nodes in topological order. For each node in topological
 * order, we given the initial state and the number of balls that pass through it, we can determine
 * the number of balls that go left and the number of balls that go right, as well as the end state
 * of the switch. We can then update the number of balls that pass to the left and right node. Remember to
 * handle long long.
 * 
 * Time: O(V + E), Space: O(V + E)
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

ll n, b;
vector<vector<int>> adjlist;  // adjlist[i] = {left, right}
vector<ll> balls;
vector<bool> isright;

vector<int> ts, dist;
void toposort(int u) {
    dist[u] = 1;
    for (auto v : adjlist[u]) {
        if (dist[v] == 0) {
            toposort(v);
        }
    }
    ts.push_back(u);
}

int main() {
    fast_cin();
    cin >> b >> n;
    n++;
    adjlist.assign(n, vi());
    balls.assign(n, 0);
    isright.assign(n, false);

    balls[1] = b;

    for (int i = 1; i < n; i++) {
        char state;
        cin >> state;
        if (state == 'R') {
            isright[i] = true;
        }
        int v;
        cin >> v;
        adjlist[i].emplace_back(v);
        cin >> v;
        adjlist[i].emplace_back(v);
    }

    dist.assign(n, 0);
    ts.clear();
    for (int i = 0; i < n; i++) {
        if (dist[i] == 0) {
            toposort(i);
        }
    }
    reverse(ts.begin(), ts.end());
    ts.pop_back();

    for (int u : ts) {
        ll more = (balls[u] + 1LL) / 2LL;
        ll less = balls[u] / 2LL;

        if (isright[u]) {
            balls[adjlist[u][1]] += more;
            balls[adjlist[u][0]] += less;
        } else {
            balls[adjlist[u][0]] += more;
            balls[adjlist[u][1]] += less;
        }

        isright[u] = ((ll)isright[u] + balls[u]) % (2LL);
        // cout << u << " " << isright[u] << " " << balls[u] << endl;
    }
    for (int i = 1; i < n; i++) {
        cout << (isright[i] ? "R" : "L");
    }
    cout << endl;

    return 0;
}