/**Kattis - pikemanhard
 * Greedy + (Nested) Binary Search + Mathematics + Counting Sort + Prefix Sum.
 * Quite a big problem with many parts. We first observe that the optimal stategy is to do the
 * problems in increasing order of time taken.
 *
 * Then we observe that the range of times taken to solve the problems is [1..c] where c <= 1e6 so
 * we can do a counting sort to sort the problems by time taken. But this counting sort would still
 * be O(n).
 *
 * Except we observe the fact that the next time taken is only dependent on the current time taken.
 * So, if we encounter a time taken that we have already seen before, we know that we have entered a
 * cycle and we can calculate the number of times we will go around the cycle and just update all
 * the times present in the cycle. This allows us to compute the times in O(3*c) = O(c).
 *
 * Now, clearly O(n) trying to greedily take the smallest problem will TLE, so we BSTA i.e. binary
 * search for the maximum number of problems we can solve within t time. For each candidate number
 * of problems, we do another binary search to find (informally) "the longest time out of the
 * shortest m problems". This is achieved by precomputing a questionPrefixSum which contains the
 * number of questions that can individually be solved in <= i time and doing the binary search on
 * this array to find the largest index that is <= m. We can then determine the time taken to solve
 * the shortest m problems. Again, to ensure this is O(1) for each candidate m, we precompute a
 * timePrefixSum where timePrefixSum[i] is the time taken to solve all problems that are
 * individually solvable in <= i time.
 *
 * Then we just compute the penalty. This is achived in O(c) via some math (arithmetic progression)
 * by counting the penalties for all problems that take the same time to solve all at once. There is
 * an issue where we are multiplying 2 numbers (timeThusFar * numTake <= 1e18 * 1e9) that may
 * overflow the long long limit. As such, we need to use 128 bit integers for these numbers. This is
 * a major debugging issue.
 * 
 * Time: O(c + log n * log c), Space: O(c)
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

ll n, t, a, b, c;
vector<int> countingArr, firstInstance;
vector<ll> timePrefixSum;       // time taken to do all problems with time <= i
vector<int> questionPrefixSum;  // number of questions that can be done with time <= i
int main()
{
    fast_cin();
    cin >> n >> t;
    cin >> a >> b >> c;
    countingArr.assign(c + 1, 0);
    firstInstance.assign(c + 1, -1);
    ll ti;
    cin >> ti;
    countingArr[ti]++;
    firstInstance[ti] = 0;

    bool didJump = false;
    for (int i = 1; i < n; i++) {
        ti = (a * ti + b) % c + 1;
        if (didJump || countingArr[ti] == 0) {
            countingArr[ti]++;
            firstInstance[ti] = i;
        }
        else {
            int period = i - firstInstance[ti];
            int multiplier = (n - i) / period;
            for (int j = 0; j <= c; j++) {
                if (firstInstance[j] >= firstInstance[ti]) {
                    assert(countingArr[j] == 1);
                    countingArr[j] += multiplier;
                }
            }

            i += period * multiplier;
            if (i < n) {
                countingArr[ti]++;
            }
            assert(i <= n);
            didJump = true;
        }
    }

    timePrefixSum.assign(c + 1, 0);
    questionPrefixSum.assign(c + 1, 0);
    for (int i = 1; i <= c; i++) {
        timePrefixSum[i] = timePrefixSum[i - 1] + countingArr[i] * i;
        questionPrefixSum[i] = questionPrefixSum[i - 1] + countingArr[i];
    }

    int l = 0, r = n;
    int left0 = 0, right0 = c;
    while (l < r) {
        int m = (l + r + 1LL) / 2LL;
        // we try doing m problems

        // find the largest index i such that questionPrefixSum[i] <= m
        int left = left0, right = right0;
        while (left < right) {
            ll mid = (left + right + 1LL) / 2LL;
            if (questionPrefixSum[mid] > m) {
                right = mid - 1;
            }
            else {
                left = mid;
            }
        }
        assert(questionPrefixSum[left] <= m);
        ll timeTaken = timePrefixSum[left] + (ll)(m - questionPrefixSum[left]) * (ll)(left + 1LL);

        if (timeTaken <= t) {
            l = m;  // do more problems
            left0 = left;
        }
        else {
            r = m - 1;
            right0 = right;
        }
    }
    ll penalty = 0;
    __int128 timeThusFar = 0;
    __int128 numTake = 0;
    int MOD = 1e9 + 7;
    int curIndex = 0;
    for (int i = 0; i < l;) {
        while (countingArr[curIndex] == 0) {
            curIndex++;
        }
        numTake = min(countingArr[curIndex], l - i);
        penalty += (timeThusFar * numTake) % MOD;
        penalty %= MOD;
        penalty += (curIndex * ((numTake * (numTake + 1)) / 2LL) % MOD) % MOD;
        penalty %= MOD;
        timeThusFar += curIndex * numTake;
        i += numTake;
        curIndex++;

        assert(i <= l);
    }
    cout << l << " " << penalty << endl;

    return 0;
}