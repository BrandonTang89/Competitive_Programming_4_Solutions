/**Kattis - wordspin
 * Observe that it is not required to make shifts of different directions onto the same character
 * since for each shift backwards to counter the wrong shift, we can just shift the stuff adjacent
 * to the character directly. E.g. instead of aca -> bdb -> bbb, we can just aca -> bca -> bba ->
 * bbb which use the same number of moves.
 *
 * Consider the first character of each word, due to the previous observation, we can see that we
 * should just directly fix this. Following which, when we consider the second character from the
 * left. If we need to shift it in the same direction as the first character, we can make use of
 * some of the shifts we made in the first character to reduce the number of shifts from the second
 * character. If we need to shift it in the opposite direction, then we should just shift only the
 * second character (and possibly some characters to the right of it but none to the left). Repeat
 * this for the entire string.
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

string a, b;
int main() {
    fast_cin();
    cin >> a >> b;
    int n = a.size();
    int prev = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = b[i] - a[i];
        if (cur * prev > 0) {
            // cur and prev same direction
            ans += max(0, abs(cur) - abs(prev));
        } else {
            ans += abs(cur);
        }
        prev = cur;
    }
    cout << ans << endl;

    return 0;
}