/**Kattis - ibaord
 * Simple problem, just read chars as ascii ints and count the number of 1s and 0s mod 2.
 * Time: O(n), Mem: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    while (getline(cin, s)) {
        int zeros = 0, ones = 0;
        for (auto c : s) {
            int cur = __builtin_popcount(int(c));
            zeros += 7 - cur;
            ones += cur;
        }
        if (zeros & 1 || ones & 1)  // mod 2
            cout << "trapped" << endl;
        else
            cout << "free" << endl;
    }

    return 0;
}