/**Kattis - digitdivision
 * Math. First consider the set (S) of all valid subsequences from the start until some point.
 * Observe that the subsequences between the boundaries of the subsequences in S are also valid.
 * Consider the subsequence in the boundary between xm and ym where x < y. Note that the number
 * formed by this subsequence is equal to ym - xm  which is divisible by m and so is a valid
 * subsequence.
 *
 * Now observe that all relevant valid subsequences start and end at the boundaries of S. Assume
 * that some valid subsequence starts at a boundary of S and doesn't end at a boundary of S. The
 * number represented by the digits from the start to the end point of this subsequence is not
 * divisible by m. Since the number from the start to the start point of this subsequences is
 * divisible by m, the sum of digits within the sequence is not divisible by m (contradiction).
 *
 * Now assume some valid subsequence Q starts not at a boundary of S. The leftmost subsequence in a
 * partition with Q must start from the start so it will start from S, meaning there is a
 * subsequence on the left of Q that starts from a boundary of S and doesn't end at a boundary of S.
 * For this subsequence have the same contradiction as before, meaning that Q is irrelevant since we
 * will never be able to use it in any partition.
 *
 * As such, we only need to consider partitions formed by the boundaries of S. We can either use
 * each boundary or not so this gives us 2^(num_boundaries) = 2^(num_subsequences_of_S) partitions.
 *
 * Note that in finding the subsequences of S, we need to ensure that the last subsquence is also
 * valid, else there is no possible partition.
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

ll n, m, num_seg, cur; // num_seg = number of subsequences of S = number of boundaries of S + 1
ll MOD = 1e9 + 7;
inline ll mod(ll a, ll b) { return (a % b + b) % b; }

// O(log p) exponentiation with modulus
ll fexp_mod(ll b, ll p, ll m)
{
    if (p == 0) return 1;

    ll ans = fexp_mod(b, p >> 1, m);
    ans = mod(ans * ans, m);
    if (p & 1) ans = mod(ans * b, m);
    return ans;
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        ll a = c - '0';
        cur *= 10;
        cur += a;
        cur %= m;
        if (cur == 0) {
            num_seg++;
        }
    }
    if (num_seg == 0 || cur != 0) { // important to check cur != 0
        cout << 0 << endl;
        return 0;
    }
    cout << fexp_mod(2, num_seg - 1, MOD) << endl;

    return 0;
}