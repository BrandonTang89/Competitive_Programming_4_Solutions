/**Kattis - data
 * This is one of my first legit chapter combination questions.
 *
 * The mathematics part is relatively simple. We just need to pre-compute the number of distinct
 * prime factors for each number between 0 and 14000 inclusive. This is because any sum of data that
 * a customer can buy will fall within this range.
 *
 * The DP part is slightly more complex. We let the state be (bitmask, c) where bitmask is the set
 * of data that customers < c have already bought, and c is the current customer. set bits are still
 * available. We use this format to allow the use of LSOne to get the available data. Now, once we
 * know the available data, we check customer c taking all possible subsets of the data. This is
 * done with another bitmask on the available data (ya this is the confusing part). We then check
 * which subset gives the maximum answer.
 *
 * State Space: O(2^n * n)
 * Transition: O(2^n)
 *
 * Time: O(2^(n+1) * n)
 * Space: O(2^n * n)
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
#define LSOne(S) (S & (-S))

/**fill_numDiffPF Computes the Number of Distinct Prime Factors
 * for all numbers from 0 to _upperbound inclusively
 *
 * @param _upperbound The upper bound for the numbers
 * numDiffPF[i] = number of distinct prime factors of i
 */
vector<int> numDiffPF;
void fill_numDiffPF(int _upperbound) {
    numDiffPF.assign(_upperbound, 0);
    for (int i = 2; i <= _upperbound; i++) {
        if (numDiffPF[i] == 0) {  // i is prime
            for (int j = i; j <= _upperbound; j += i) {
                numDiffPF[j]++;  // j is divisible by prime i
            }
        }
    }
}

int n, d;
vector<int> arr;
int memo[(1 << 14)][14];
int dp(int bm, int c) {  // returns the max possible revenue, assume customers < c already done
    // bm & (1 << i) == 1 if data i is not used
    if (c >= n) {
        if (bm == 0)
            return 0;
        else
            return -(int)1e7;
    }
    if (memo[bm][c] != -1) return memo[bm][c];
    // iterate all possible subsets of non selected bits
    vector<int> available;
    int mask = bm;
    while (mask > 0) {
        int two_pow_i = LSOne(mask);
        mask -= two_pow_i;

        available.push_back(two_pow_i);
    }

    int max_mask = (1 << (int)available.size()) - 1;
    int ans = 0;
    for (int i = 0; i <= max_mask; i++) {  // i is a bitmask
        // all on bits are selected by customer c
        int next_mask = bm;
        mask = i;
        int sum_for_c = 0;
        while (mask > 0) {
            int two_pow_i = LSOne(mask);
            mask -= two_pow_i;
            int idx = __builtin_ctz(two_pow_i);
            next_mask &= ~(available[idx]);

            sum_for_c += arr[__builtin_ctz(available[idx])];
        }
        ans = max(ans, dp(next_mask, c + 1) + numDiffPF[sum_for_c]);
    }

    // printf("bm: %d, c: %d, ans: %d\n", bm, c, ans);
    return memo[bm][c] = ans;
}

int main() {
    fast_cin();
    fill_numDiffPF(14005);
    memset(memo, -1, sizeof memo);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> d;
        arr.push_back(d);
    }

    cout << dp((1 << n) - 1, 0) << endl;

    return 0;
}