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

int n, m;
const int top = 1e6 + 1;
bool comp(pair<int, int> a, pair<int, int> b)
{  // sort by increasing difference
    if (a.first - a.second < b.first - b.second) return true;
    if (a.first - a.second > b.first - b.second) return false;
    return a.first < b.first;
}
int main()
{
    fast_cin();
    vector<int> memo;                // memo[i] is the maximum XP gained if we have i ingots
    vector<pair<int, int>> options;  // options[i] is the pair of (used, recovered) for each item

    cin >> n >> m;
    options.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> options[i].first;
    }
    for (int i = 0; i < n; i++) {
        cin >> options[i].second;
    }
    sort(options.begin(), options.end(), comp);
    vector<pair<int, int>> pruned;
    pruned.push_back(options[0]);
    for (int i = 1; i < n; i++) {
        if (options[i].first - options[i].second == pruned.back().first - pruned.back().second)
            continue;
        if (options[i].first >= pruned.back().first) continue;
        pruned.push_back(options[i]);
    }
    n = pruned.size();

    int j = n - 1;
    memo.assign(top + 1, 0);
    for (int i = 0; i <= top; i++) {
        while (j - 1 >= 0 && pruned[j - 1].first <= i) j--;
        if (pruned[j].first <= i) {
            memo[i] = 1 + memo[i - pruned[j].first + pruned[j].second];
        }
    }

    reverse(pruned.begin(), pruned.end());
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        int prevIdx = 0;

        if (x <= top) {
            ans += memo[x];
            continue;
        }
        // binary search for the largest index j such that pruned[j].first <= x
        int idx = upper_bound(pruned.begin() + prevIdx, pruned.end(), make_pair(x, (int)1e9 + 10)) -
                  1 - pruned.begin();
        if (idx < 0) break;
        prevIdx = idx;
        ll maxIter = (x - pruned[idx].first) / (pruned[idx].first - pruned[idx].second) + 1;
        ans += maxIter;
        x -= maxIter * (pruned[idx].first - pruned[idx].second);
        assert(x >= 0 && x <= pruned[idx].first && x <= top);
        ans += memo[x];
    }
    cout << ans * 2 << endl;
    return 0;
}