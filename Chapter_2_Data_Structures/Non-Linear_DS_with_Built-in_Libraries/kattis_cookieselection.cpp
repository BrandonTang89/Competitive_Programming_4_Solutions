/**Kattis - cookieselection
 * Relatively simple dynamic order statistic tree problem. Just ensure that we allow duplicate values
 * in the tree and that we use long long. 
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

string s;
ost T;
ll n, pos;
int main() {
    while (cin >> s){
        if (s != "#"){
            T.insert(stoll(s));
        }
        else{
            n = T.size();
            if (n&1){
                pos = (n-1)/2;
            }
            else{
                pos = n/2;
            }
            cout << *T.find_by_order(pos) << endl;
            T.erase(T.find_by_order(pos));
        }
    }
    return 0; 
}