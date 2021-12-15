/**Kattis - bank
 * Key Observation:
 *
 * Assume that the optimal selection for times 0 to t are (x0, x1, ..., xk), k<=t. At t+1, we should
 * obviously include the largest values that expires at t+1 until we have up to t+2 values in our
 * selection. But what about the rest of the values? Well, if they are larger than any previously
 * selected value xi, then we should kick out xi and instead choose to include a value that expires
 * at t+1 that is larger than xi.
 *
 * In terms of implementation, we keep our selected values as a min heap while we use a vector of
 * max heaps to keep track of the values that expire at t for all t. Then for each t, we include the
 * the largest values that expire at t into the selected heap (as many as possible without having
 * to kick out older selected values). Then we start replacing the inferior values if the top of the
 * max heap is larger than the smallest value in the selected heap.
 *
 * Time: O(n log n + t), Space: O(n + t)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, total_t;
vector<priority_queue<int>> v;
priority_queue<int, vector<int>, greater<int>> selected;
int main() {
    cin >> n >> total_t;
    v.assign(total_t, priority_queue<int>());
    for (int i = 0; i < n; i++) {
        int c, t;
        cin >> c >> t;
        v[t].push(c);
    }
    for (int i = 0; i < total_t; i++) {
        while ((int)selected.size() < i + 1 && !v[i].empty()) {
            selected.push(v[i].top());
            v[i].pop();
        }

        while (!v[i].empty() && v[i].top() > selected.top()) {
            selected.pop();
            selected.emplace(v[i].top());
            v[i].pop();
        }
    }
    ll ans = 0;
    while (!selected.empty()) {
        ans += selected.top();
        selected.pop();
    }
    cout << ans << endl;

    return 0;
}