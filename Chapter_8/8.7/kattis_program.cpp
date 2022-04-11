/**Kattis - program
 * Another sketchy feeling question. Its mostly just.. following instructions? Just 2 optimisations:
 * 1. using DP RSQ after doing all the operations
 * 2. collecting all the jumps first and then not redoing repeated jumps.
 * 
 * Time: O(n*k), Space: O(n) but i guess still good enough to AC.
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

int n, k;
int arr[(int)1e6 + 2];
void something(int jump, int amt) {
    int i = 0;
    while (i < n) {
        arr[i] = arr[i] + amt;
        i = i + jump;
    }
}
ll ps[(int)1e6 + 2];    // prefix_sum
ll rsq(int l, int r) {  // range sum from l to r inclusively
    if (l == 0) return ps[r];
    return (ps[r] - ps[l - 1]);
}
int main() {
    fast_cin();
    cin >> n >> k;
    unordered_map<int, int> mp;
    for (int i = 0; i < k; i++) {
        int j;
        cin >> j;
        mp[j]++;
    }
    for (auto j : mp) {
        something(j.first, j.second);
    }
    for (int i = 0; i < n; i++) {
        ps[i] = arr[i];
        if (i > 0) ps[i] += ps[i - 1];
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << rsq(l, r) << endl;
    }

    return 0;
}