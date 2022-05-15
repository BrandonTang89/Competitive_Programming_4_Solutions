/**Kattis - srednji
 * The O(n^2) solution should be obvious, we use 2 for loops that itereate over the number of
 * elements removed from the left and from the right. However, we notice that for any number of
 * elements removed from the left, we can determine a value num_above_b which represents the number
 * of elements on the left of b which are > b minus the number of elements < b. We can also define
 * this value for any number of elements removed from the right side. Note that the 2 values of
 * num_above_b on the left and right must sum to 0 for b to be the median. We can use a map to store
 * the number of elements where num_above_b is a specific value x for each value removed on the
 * right. We can then iterate over the elements on the left of b and for each num_above_b, we add
 * m[-num_above_b] to our answer.
 *
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, b;
int b_pos;
vector<int> v;
unordered_map<int, int> m;
int main() {
    cin >> n >> b;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        if (v[i] == b) b_pos = i;
    }
    int num_above_b = 0;
    for (int i = b_pos; i < n; i++) {
        if (v[i] > b)
            num_above_b++;
        else if (v[i] < b)
            num_above_b--;
        m[num_above_b]++;
    }
    int ans = 0;
    num_above_b = 0;
    for (int i = b_pos; i >= 0; i--) {
        if (v[i] > b)
            num_above_b++;
        else if (v[i] < b)
            num_above_b--;
        ans += m[-num_above_b];
    }
    cout << ans << endl;

    return 0;
}