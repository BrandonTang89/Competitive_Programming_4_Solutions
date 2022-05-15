/**Kattis - marblestree
 * Surprisingly involved implementation for a "easy greedy problem". The key insight in this case
 * is that we consider the leaves, if a leaf has >= 1 marble, we move all except 1 out of the leaf,
 * if the leaf has no marbles, we move a marble into the leaf. We can then update the number of
 * marbles that the parent has, note that it is alright fot a leaf to have negative marbles. Once
 * all the children of a internal node have been processed, it becomes a leaf and we repeat the process
 * on it. In practise, we use a queue to store the current leaf nodes to be processed.
 * 
 * Time: O(n), Space: O(n)
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

int n, u, num_c, c;
vector<vector<int>> children;
vector<int> parent, marbles, children_left;
queue<int> leaves;
ll ans;
int main() {
    fast_cin();
    while (true) {
        cin >> n;
        if (n == 0) break;
        marbles.assign(n, 0);
        children.assign(n, vi());
        parent.assign(n, -1);
        children_left.assign(n, 0);
        ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> u >> marbles[i] >> num_c;
            for (int j = 0; j < num_c; j++) {
                cin >> c;
                c--;
                children[i].push_back(c);
                parent[c] = i;
            }
            if (num_c == 0) leaves.push(i);
            children_left[i] = num_c;
        }

        while (!leaves.empty()) {
            int curr = leaves.front();
            leaves.pop();
            ans += abs(marbles[curr] - 1);
            if (parent[curr] == -1) continue;
            marbles[parent[curr]] += marbles[curr] - 1;
            children_left[parent[curr]]--;

            if (children_left[parent[curr]] == 0) leaves.push(parent[curr]);
        }

        cout << ans << endl;
    }

    return 0;
}