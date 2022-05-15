/**Kattis - bst
 * Contrary to what you might think, we shouldn't actually construct a BST as that would be O(n^2) in
 * the worst case scenerio. Instead we use a bbst and a hashtable.
 * 
 * Obervation:
 * Given a partially constructed BST, if we insert a node with value x where y<x<z where y is the largest
 * value in the tree smaller than x and z is the smallest value in the tree larger than x, then we can
 * say that the depth of x will be 1 + max(depth(y), depth(z)).
 * 
 * Using this obeservation, the rest of the code should be understandable.
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int n, x;
ll ans = 0;
set<int> s;
unordered_map<int, int> m;  // m[i] = depth of element i

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x;
        auto it = s.insert(x).first;  // returns an iterator to the element that was just inserted

        if (it == s.begin() && *--s.end() == x) {
            m[x] = 0;
        } else if (it == s.begin()) {
            m[x] = m[*++it] + 1;
        } else if (it == --s.end()) {
            m[x] = m[*--it] + 1;
        } else {
            m[x] = m[*--it]; // one to the left
            m[x] = max(m[x], m[*++(++it)]); // one to the right
            m[x]++;
        }

        ans += m[x];
        cout << ans << endl;
    }

    return 0;
}