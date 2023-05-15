/**Kattis - reducedidnumbers
 * Straightforward complete search + hash set. Just check all possible modulus until we find one that works.
 * 
 * Time: O(n * 1e6), Space: O(n)
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

int n;
vector<int> nums;
unordered_set<int> s;
int main()
{
    fast_cin();
    cin >> n;
    nums.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 1; i <= 1e6-1; i++) {
        s.clear();
        for (auto num : nums) {
            int m = num % i;
            if (s.find(m) != s.end()) {
                break;
            }
            s.insert(m);
        }
        if ((int)s.size() == n) {
            cout << i << endl;
            return 0;
        }
    }
    assert(false);

    return 0;
}