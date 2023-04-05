/**Kattis - sumsets
 * Somewhat of a meet in the middle. We're trying to find a+b = d-c. So we start by finding all a+b
 * and storing them in a map (apb -> [(a, b) such that a+b = apb]) in O(n^2). Then we iterate
 * through all d, c and check the map. If d-c is a key in the map, we check if there is a pair (a,
 * b) such all a, b, c, d are distinct.
 *
 * We make this slightly more efficient on average by sorting the array and then iterating from
 * larger values of d downwards. This is because we want to find the largest d possible. Then we
 * return upon finding a valid d.
 *
 * Time: O(somewhere between n^2 and n^3), Mem: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
vector<ll> v;
unordered_map<ll, vector<pair<ll, ll>>> mp;
int main()
{
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            mp[v[i] + v[j]].push_back({v[i], v[j]});  // a+b, a, b
        }
    }

    for (int i = n - 1; i >= 0; i--) {  // d
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (mp.find(v[i] + v[j]) != mp.end()) {
                for (auto p : mp[v[i] - v[j]]) {  // d - c
                    if (p.first != v[i] && p.first != v[j] && p.second != v[i] &&
                        p.second != v[j]) {
                        cout << v[i] << endl;
                        return 0;
                    }
                }
            }
        }
    }
    cout << "no solution" << endl;

    return 0;
}