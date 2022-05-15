/**Kattis - busnumbers2
 * Kinda weird going back to easy questions after spending so much time in the 5-8 difficulty
 * range with 100+ lines of code per question. We just find all sums of cubes of 2 distinct numbers
 * under the upperbound. Then we get the largest. We can tell if a number can be represented in 2
 * different ways by just using a hashmap to store the numbers that have already been represented
 * at least once before.
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

unordered_set<int> s;
int main() {
    int ans = -1;
    int ub;
    cin >> ub;
    for (int i = 1; i <= cbrt(ub); i++) {
        for (int j = i; j <= cbrt(ub); j++) {
            if (i * i * i + j * j * j > ub) break;

            if (s.find(i * i * i + j * j * j) == s.end()) {
                s.insert(i * i * i + j * j * j);
            } else {
                ans = max(ans, i * i * i + j * j * j);
            }
        }
    }
    cout << (ans == -1 ? "none" : to_string(ans)) << endl;
    return 0;
}