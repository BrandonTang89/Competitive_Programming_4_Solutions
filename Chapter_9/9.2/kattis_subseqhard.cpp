/**Kattis - subseqhard
 * Got baited by the hint. While it looks like a sliding window variant, we don't actually
 * use the sliding window technique, rather we use a hashtable. This is basically a variant
 * of finding the number of subarrays that sum to 0. We maintain a running prefix sum and
 * record all prefix sums in an hashtable, we then check whether theres a previous prefix-sum
 * which is equal to the current sum - 47, meaning the subarray between the current and previous
 * indices is 47. Also note the edge case of the running sum itself being 47.
 *
 * Time: O(n), Space: O(n)
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

int n, num_tc;
ll a;
unordered_map<ll, ll> m;
int main() {
    cin >> num_tc;
    while (num_tc--) {
        m.clear();
        cin >> n;
        ll cur_sum = 0;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> a;
            cur_sum += a;

            ans += m[cur_sum - 47] + (cur_sum == 47);
            m[cur_sum]++;
        }
        cout << ans << endl;
    }

    return 0;
}