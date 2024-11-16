#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
vector<vector<int>> children;
vector<int> memo;

void dfs(int u) {
    for (auto v : children[u]) {
        dfs(v);
    }

    priority_queue<int, vector<int>, greater<int>> pq;  // min heap
    int count = 0;
    for (auto v : children[u]) {
        pq.push(memo[v]);
        count++;
    }

    while (count > 2) {
        int least = pq.top();
        pq.pop();
        int second_least = pq.top();
        pq.pop();
        pq.emplace(max(least, second_least) + 1);
        count--;
    }

    if (count == 0) {
        memo[u] = 0;
    } else if (count == 1) {
        memo[u] = pq.top() + 1;
    } else {
        pq.pop();
        memo[u] = pq.top() + 1;
    }
}
int main() {
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        children.assign(n, vector<int>());
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;
            children[p].push_back(i);
        }

        memo.assign(n, -1);
        dfs(0);
        cout << memo[0] << endl;
    }

    return 0;
}