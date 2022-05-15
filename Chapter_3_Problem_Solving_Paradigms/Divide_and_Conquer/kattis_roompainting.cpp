/**Kattis - roompainting
 * Basic binary search on a vector.
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;

int n, m, q;
ll total_wasted = 0;
vector<int> paints;
int main(){
    cin >> n >> m; 
    paints.assign(n, 0);
    for (int i=0; i<n;i++){
        cin >> paints[i];
    }
    sort(paints.begin(), paints.end());

    for (int i=0; i<m; i++){
        cin >> q; 
        int index = lower_bound(paints.begin(), paints.end(), q) - paints.begin();
        total_wasted += paints[index] - q;
    }
    cout << total_wasted << endl;

    return 0;
}