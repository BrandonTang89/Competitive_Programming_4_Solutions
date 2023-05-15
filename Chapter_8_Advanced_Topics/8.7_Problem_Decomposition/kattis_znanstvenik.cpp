/**Kattis - znanstvenik
 * Strings. Observe that if let S = {s1, s2, ..., sC} be the set of strings where si = (column i
 * read from bottom to top) then our answer is R-LCP(S)-1 where LCP(S) is the longest common prefix.
 * We can compute this efficiently by first sorting the strings then just comparing adjacent
 * strings.
 *
 * Note that we should be careful when building the strings to avoid unnecessary copying. It seems
 * like using strings[j] += c ensures that we don't copy the string unnecessarily (as opposed to
 * strings[j] = strings[j] + c).
 *
 * Time: O(RC * log C), Space: O(RC)
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

int numStrings, lenStrings;
vector<string> strings;
int main()
{
    fast_cin();
    cin >> lenStrings >> numStrings;
    strings.assign(numStrings, "");

    for (int i = 0; i < lenStrings; i++) {
        for (int j = 0; j < numStrings; j++) {
            char c;
            cin >> c;
            strings[j] += c;
        }
    }

    for (int i = 0; i < numStrings; i++) {
        reverse(strings[i].begin(), strings[i].end());
    }

    sort(strings.begin(), strings.end());

    int lcp = 0;
    for (int i = 0; i < numStrings - 1; i++) {
        int common = 0;
        // find LCP of strings[i] and strings[i+1]
        for (int j = 0; j < lenStrings; j++) {
            if (strings[i][j] == strings[i + 1][j]) {
                common++;
            }
            else {
                break;
            }
        }
        lcp = max(lcp, common);
    }

    cout << lenStrings - lcp - 1 << endl;
    return 0;
}