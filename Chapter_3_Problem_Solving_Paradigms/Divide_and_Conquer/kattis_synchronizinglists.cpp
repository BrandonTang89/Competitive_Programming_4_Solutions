/**Kattis - synchronizinglists
 * While there might be other ways to solve this problem, I opt to just use the C++ order statistics tree to
 * determine the rank of a[i] and then select the element in b[i] with the corresponding rank.
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ost;
typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int main() {
    fast_cin();
    while (1) {
        int n;
        cin >> n;
        if (n == 0) break;
        ost atree, btree;
        vector<int> a, b;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            atree.insert(a[i]);
        }
        b.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            btree.insert(b[i]);
        }

        for (int i = 0; i < n; i++) {
            cout << *btree.find_by_order(atree.order_of_key(a[i])) << endl;
        }
        cout << endl;
    }
    return 0;
}