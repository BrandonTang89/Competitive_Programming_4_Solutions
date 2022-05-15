/**Kattis - megainversions
 * An order statistics question. We can easily see that for a given center, we should try to find the
 * number of larger elements to the left and number of smaller elements to the right, in O(log n). This is
 * actually order statistics ranking. However, since we are dealing with an array of repeated elements,
 * we need to use a PBDS that uses pair (element, index) as the key. This ensures every pair is unique.
 * Then to get the number of elements strictly smaller than element, search for (element, 0) while
 * if we want to search for elements smaller than or equal to the element, search for (element, n+1).
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
             tree_order_statistics_node_update> ost; // multiset with order statistics


typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
vector<int> v, second_label;
int main(){
    cin >> n;
    v.resize(n);
    ost left, right;
    for (int i=0; i<n; i++){
        cin >> v[i];
        right.insert({v[i], i});
    };

    ll ans = 0; 
    for (int center=0; center<n; center++){
        left.insert({v[center], center});
        ll left_rank = left.size() - left.order_of_key({v[center], n+1}); // number of items that are strictly smaller than v[center]
        ll right_rank = right.order_of_key({v[center], 0}); // number of items that are strictly smaller than v[center]
        right.erase({v[center], center});
        ans += left_rank * right_rank;
    }
    cout << ans << endl;



    return 0;
}