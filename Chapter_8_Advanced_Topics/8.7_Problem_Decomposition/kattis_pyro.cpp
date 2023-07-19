/**Kattis - pyro
 * Math + data structure + complete search. Quite an easy question. For each L value, we just try
 * all numbers that differ by 1 or 2 states. This can be done efficiently by xoring the changes with
 * the L value. Then we just check if the new value is greater and is another value in the list
 * using a hashset.
 * 
 * Time: O(n * 18^2), Space: O(n)
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

vector<int> arr;
unordered_set<int> s;
int main()
{
    fast_cin();
    while (true) {
        int l;
        cin >> l;
        if (l == -1) break;
        arr.emplace_back(l);
        s.insert(l);
    }

    for (int i = 0; i < (int)arr.size(); i++) {
        int ans = 0;
        for (int j = 0; j < 18; j++) {
            int x = arr[i] ^ (1 << j);
            if (x > arr[i] && s.find(x) != s.end()) {
                ans++;
            }
        }

        for (int j = 0; j < 18; j++) {
            for (int k = j + 1; k < 18; k++) {
                int x = arr[i] ^ (1 << j) ^ (1 << k);
                if (x > arr[i] && s.find(x) != s.end()) {
                    ans++;
                }
            }
        }
        cout << arr[i] << ":" << ans << endl;
    }

    return 0;
}