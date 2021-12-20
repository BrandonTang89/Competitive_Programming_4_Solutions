/**Kattis - continuousmedian
 * Relatively simple dynamic order statistic tree problem. 
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> ost;

ll n, pos, num_tc, x;
ll mean(ll a, ll b){
    return (a+b)/2;
}
int main() {
    cin >> num_tc;
    for (int tc=0;tc<num_tc;tc++){
        ost T;
        ll ans = 0;
        cin >> n;

        for (int i=1; i<=n; i++){
            cin >> x;
            T.insert(x);

            if (i&1){
                ans += *T.find_by_order((i-1)/2);
            }
            else{
                ans += mean(*T.find_by_order((i-1)/2), *T.find_by_order(i/2));
            }
        }
        cout << ans << endl;
    }
    return 0; 
}