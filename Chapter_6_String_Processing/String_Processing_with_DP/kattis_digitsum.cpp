/**Kattis - digitsum
 * Kinda similar in some ways to cudak. Let sumUnder(xs) be the digit sum of all numbers <= xs.
 * We use the subroutine rec(n) that returns the digit sum of all n digit numbers allowing for
 * leading zeros. Just inspect the code, it's not terribly hard.
 *
 * Time: O(length xs), Space: O(length xs)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll memo2[17];
ll tenpow(int n) // 10^n
{
    if (memo2[n] != -1) return memo2[n];
    if (n == 0) return (memo2[n] = 1);
    return (memo2[n] = 10LL * tenpow(n - 1));
}
ll memo[16];
ll rec(int numDigits)
{
    if (memo[numDigits] != -1) return memo[numDigits];
    if (numDigits == 0) return (memo[numDigits] = 0);
    ll ans = 10 * rec(numDigits - 1);
    for (int i = 1; i < 10; i++) {
        ans += i * tenpow(numDigits - 1);
    }
    return (memo[numDigits] = ans);
}

ll sumUnder(string xs)
{
    ll ans = 0;
    ll curDigitSum = 0;
    for (int i = 0; i < (int)xs.size(); i++) {
        // consider all numbers with exactly i leading digits being the same as xs
        // next digit should be smaller than xs[i]
        ll curDigit = xs[i] - '0';
        for (int j = 0; j < curDigit; j++) {
            ans += (curDigitSum + j) * tenpow(xs.size() - i - 1) + rec(xs.size() - i - 1);
        }
        curDigitSum += curDigit;
    }

    for (auto c : xs) {  // also add the digits of xs
        ans += c - '0';
    }

    return ans;
}
int main()
{
    memset(memo, -1, sizeof memo);
    memset(memo2, -1, sizeof memo2);
    int tc;
    cin >> tc;
    while (tc--) {
        string as, bs;
        cin >> as >> bs;
        ll digitSumAs = 0;
        for (char c : as) digitSumAs += c - '0';
        cout << sumUnder(bs) - sumUnder(as) + digitSumAs << endl;
    }

    return 0;
}