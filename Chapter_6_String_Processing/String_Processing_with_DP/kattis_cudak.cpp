/**Kattis - cudak
 * Non-trivial counting problem...
 *
 * There are 2 parts to the problem: the first is how to count the number of numbers in the range.
 * We start by observing that we should make a function solve(xs, x, digitSum) that returns the
 * number of numbers <= x that have their digits sum to digitSum. We can do this by considering
 * 2 types of numbers, numbers with less total digits than x and numbers with the same number of
 * digits as x.
 *
 * For the first type of numbers, we can just directly call rec(numDigits, digitSum) which
 * returns the number of numbers that have numDigits digits and sum to digitSum (allowing for
 * leading 0s).
 *
 * For the second type of numbers, we go along the digits of x and consider the numbers that
 * are less <= x by having the same leading digits as x but then having smaller digits after.
 *
 * The other part is finding the smallest number in the interval. This is done by recursive
 * backtracking + pruning. We try numbers with increasing digit length, with the smallest that we
 * consider being the smallest number with the same number of digits as a and with 9*num digits >=
 * s i.e. can divide s into all the digits.
 *
 * Our recursion processes the numbers in increasing order so we only need to consider the first
 * valid number. We make 2 important pruning observations:
 * 1. If digitsLeft * 9 < digitSum: we cannot fit all digitSum into the remaining digits so we
 * return
 * 2. If the length we are considering is the same as the length of a and the previously selected
 *    leading digits are the same as that of a, the next digit should start from at least the next
 *    digit of a. Doing this ensures that we can only validly construct numbers >= a.
 * 
 * Time: O(? difficul to analyse the pruning part), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll a, b;
int s;
ll ans, mini;
string as, bs;
vector<vector<ll>> memo;
ll rec(int numDigits, int digitSum)
{
    if (digitSum < 0) return 0;
    if (memo[numDigits][digitSum] != -1) return memo[numDigits][digitSum];
    if (numDigits == 0) return (memo[numDigits][digitSum] = (digitSum == 0 ? 1 : 0));

    ll &ans = memo[numDigits][digitSum];
    ans = 0;
    for (int i = 0; i < min(10, digitSum + 1); i++) {
        ans += rec(numDigits - 1, digitSum - i);
    }
    return ans;
}

ll solve(string xs, ll x, int digitSum)
{  // number of numbers <= x that have digitSum
    ll numDigits = xs.size();
    ll ans = 0;
    for (int i = 1; i < numDigits; i++) {
        for (int j = 1; j < 10; j++) {
            ans += rec(i - 1, digitSum - j);
        }
    }
    ll curDigitSum = 0;
    for (int i = 0; i < numDigits; i++) {
        ll curDigit = xs[i] - '0';
        for (int j = 0; j < curDigit; j++) {
            if (i == 0 && j == 0) continue;
            ans += rec(numDigits - i - 1, digitSum - curDigitSum - j);
        }
        curDigitSum += curDigit;
    }
    return ans;
}

ll smallest = 1e18;
ll considering = -1;
void getSmallest(ll cur, ll digitsLeft, ll digitSum)
{
    if (digitSum < 0) return;
    if (digitsLeft * 9 < digitSum) return;
    if (digitsLeft == 0 && digitSum == 0) {
        if (cur >= a && cur <= b) {
            smallest = min(smallest, cur);
        }
        return;
    }
    if (digitsLeft == 0) return;
    int start = (cur == 0 ? 1 : 0);
    if (considering == (int)as.size()) {
        ll temp = a;
        for (int i = 0; i < digitsLeft; i++) {
            temp /= 10;
        }
        // temp is the leading section of a
        if (temp == cur) start = as[(int)as.size() - digitsLeft] - '0';
    }
    for (ll i = start; i < 10 && smallest == 1e18; i++) {  //
        getSmallest(cur * 10LL + i, digitsLeft - 1, digitSum - i);
    }
}
int main()
{
    memo.assign(16, vector<ll>(150, -1));

    cin >> as >> bs >> s;
    a = stoll(as);
    b = stoll(bs);
    cout << solve(bs, b, s) - solve(as, a - 1, s) << endl;

    // time to get the smallest
    for (considering = (int)as.size(); considering <= 15 && smallest == 1e18; considering++) {
        if (9 * considering < s) continue;  // not big enough
        getSmallest(0, considering, s);
    }
    assert(smallest != 1e18);
    cout << smallest << endl;

    return 0;
}