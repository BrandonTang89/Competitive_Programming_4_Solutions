/**Kattis - ceremony
 * It should be obvious that if we try to blow all the xth floors, we should always choose x = 1, ie
 * remove 1 floor from all buildings that aren't already destroyed. For any valid series of moves,
 * the order doesn't matter, ie we can assume that we do all the blow 1 floor moves before all the
 * delete block moves. So we just need to check all of such types of strategies. First we sort the
 * buildings by height, then process in ascending order of height, for each building, we try to blow
 * all buildings at that height or smaller floor by floor, then blow the rest manually. 
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> v;
int main() {
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());

    int ans = n;                   // blow all the buildings 1 by 1
    for (int i = 0; i < n; i++) {  // reduce up to building i to rubble then delete the rest
        ans = min(ans, v[i] + (n - i - 1));
    }
    cout << ans << endl;

    return 0;
}