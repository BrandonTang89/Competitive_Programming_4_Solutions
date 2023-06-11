/**Kattis - gamenight
 * We try all possible permutations of the groups, which is actually just (3-1)! = 2! = 2
 * permutations (i.e. [abc], [acb]) since this is cyclic. For each permutation, we try to match the
 * sorted string (according to the permutation) with the given string. We update the matching
 * incrementally as we slide the sorted string along the given string and only check the positions
 * which are changed to avoid repeated work.
 * Note the useful trick of appending a copy of s to itself so we don't need to worry about the
 * cyclic nature of s.
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

int n;
string s;
int main()
{
    fast_cin();
    cin >> n >> s;
    s += s;
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A')
            a++;
        else if (s[i] == 'B')
            b++;
        else
            c++;
    }
    int ans = n;
    // try a then b then c
    int cur = 0;                   // number of matches
    for (int i = 0; i < a; i++) {  // a from [0, a-1]
        if (s[i] == 'A') cur++;
    }
    for (int i = a; i < b + a; i++) {
        if (s[i] == 'B') cur++;
    }
    for (int i = b + a; i < n; i++) {
        if (s[i] == 'C') cur++;
    }
    ans = min(ans, n - cur);
    for (int i = 1; i < n;
         i++) {  // a from [i, i+a-1], b from [i+a, i+a+b-1], c from [i+a+b, i+a+b+c-1]
        if (s[i - 1] == 'A') cur--;
        if (s[i + a - 1] == 'A') cur++;
        if (s[i + a - 1] == 'B') cur--;
        if (s[i + a + b - 1] == 'B') cur++;
        if (s[i + a + b - 1] == 'C') cur--;
        if (s[i + a + b + c - 1] == 'C') cur++;
        ans = min(ans, n - cur);
    }

    // try a then c then b
    cur = 0;
    for (int i = 0; i < a; i++) {  // a from [0, a-1]
        if (s[i] == 'A') cur++;
    }
    for (int i = a; i < c + a; i++) {
        if (s[i] == 'C') cur++;
    }
    for (int i = c + a; i < n; i++) {
        if (s[i] == 'B') cur++;
    }
    ans = min(ans, n - cur);
    for (int i = 1; i < n;
         i++) {  // a from [i, i+a-1], c from [i+a, i+a+c-1], b from [i+a+c, i+a+b+c-1]
        if (s[i - 1] == 'A') cur--;
        if (s[i + a - 1] == 'A') cur++;
        if (s[i + a - 1] == 'C') cur--;
        if (s[i + a + c - 1] == 'C') cur++;
        if (s[i + a + c - 1] == 'B') cur--;
        if (s[i + a + b + c - 1] == 'B') cur++;
        ans = min(ans, n - cur);
    }
    cout << ans << endl;

    return 0;
}