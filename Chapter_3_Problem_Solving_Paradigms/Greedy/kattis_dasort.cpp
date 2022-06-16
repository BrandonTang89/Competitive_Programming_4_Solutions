/**Kattis - dasort
 * Abit of a lame question. First of all, assume that the array is of unique elements [0..n-1], then
 * observe that the optimal way to sort requires deleting and appending all the elements that are
 * not in the correct order. E.g. 1 5 2 4 3 6 -> 1, 2, 3 are in the right order, then the rest are
 * not. So we need to delete and append the rest in the right order. It is easy to count the number
 * of elements in the right order. However, we have that the elements are not unique and they are
 * not in the range [0..n-1] so we need to make it so using some preprocessing involving a hashmap
 * and sorting.
 *
 * Time: O(n log n), Space: O(n)
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

int main() {
    fast_cin();
    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        int tc, n;
        cin >> tc >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];

        vector<int> v_copy = v;
        unordered_map<int, int> m;
        vector<int> num_each;

        sort(v_copy.begin(), v_copy.end());
        int counter = 0;
        for (int i = 0; i < n; i++) {
            if (m.find(v_copy[i]) == m.end()) {
                m[v_copy[i]] = counter++;
                num_each.push_back(1);
            } else
                num_each[m[v_copy[i]]]++;
        }

        int cur = 0;
        int okay_counter = 0;
        for (int i = 0; i < n; i++) {
            v[i] = m[v[i]];
            if (v[i] == cur) {
                num_each[cur]--;
                okay_counter++;  // correct order
                if (num_each[cur] == 0) cur++;
            }
        }

        cout << tc << " " << n - okay_counter << endl;
    }

    return 0;
}