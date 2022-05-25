/**Kattis - classpicture
 * Interative complete search - permutation. We do a mapping from names to integers based on
 * lexicographical sorting. Then we try all n! permutations and check if they are valid in
 * O(n) using a linear scan and adjacency matrix.
 * 
 * Time: O(n * n!), Space: O(n^2)
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

int n, e;
unordered_map<string, int> m;
vector<string> names;
vector<vector<int>> hates;
int main() {
    while (cin >> n) {
        ;
        names.resize(n);
        for (int i = 0; i < n; i++) cin >> names[i];
        sort(names.begin(), names.end());
        for (int i = 0; i < n; i++) m[names[i]] = i;

        hates.assign(n, vector<int>(n, 0));
        cin >> e;
        for (int i = 0; i < e; i++) {
            string n1, n2;
            cin >> n1 >> n2;
            int u = m[n1], v = m[n2];
            hates[u][v] = 1;
            hates[v][u] = 1;
        }

        vector<int> ans(n);
        for (int i = 0; i < n; i++) ans[i] = i;
        bool ok = true;
        do {
            ok = true;
            for (int i = 0; i < n - 1; i++) {
                if (hates[ans[i]][ans[i + 1]]) {
                    ok = false;
                    break;
                }
            }
            if (ok) break;
        } while (next_permutation(ans.begin(), ans.end()));
        if (ok) {
            for (int i = 0; i < n; i++) cout << names[ans[i]] << " ";
            cout << endl;
        } else
            cout << "You all need therapy.\n";
    }

    return 0;
}