/**Kattis - illiteracy
 * Obvious but tedious state-space BFS. The state is obviously the current string, and we try to get
 * from the given string to the dest string. Just tank out the annoying transitions, try to complete
 * this as fast as possible for ICPC practise ig.
 *
 * Time: O(1), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> dist;
queue<string> q;

inline char rotate(char c, int x) { return (c - 'A' + x) % 6 + 'A'; }
int main()
{
    string src, dest;
    cin >> src >> dest;
    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        string s = q.front();
        // cout << s << endl;
        q.pop();

        if (s == dest) {
            cout << dist[s] << endl;
            return 0;
        }

        for (int x = 0; x < 8; x++) {
            string newS = s;
            if (s[x] == 'A') {
                if (x < 7) {
                    newS[x + 1] = rotate(s[x + 1], 1);
                }
                if (x > 0) {
                    newS[x - 1] = rotate(s[x - 1], 1);
                }
            }
            else if (s[x] == 'B') {
                if (1 <= x && x <= 6) {
                    newS[x + 1] = newS[x - 1];
                }
            }
            else if (s[x] == 'C') {
                newS[7 - x] = rotate(s[7 - x], 1);
            }
            else if (s[x] == 'D') {
                if (x < 4) {
                    for (int i = 0; i < x; i++) {
                        newS[i] = rotate(s[i], 1);
                    }
                }
                else {
                    for (int i = x + 1; i < 8; i++) {
                        newS[i] = rotate(s[i], 1);
                    }
                }
            }
            else if (s[x] == 'E') {
                if (1 <= x && x <= 6) {
                    int y;
                    if (x < 4)
                        y = x;
                    else
                        y = 7 - x;
                    newS[x - y] = rotate(s[x - y], 1);
                    newS[x + y] = rotate(s[x + y], 1);
                }
            }
            else if (s[x] == 'F') {
                if ((x + 1) % 2 == 0) {  // x is even
                    newS[(x + 1) / 2 - 1] = rotate(s[(x + 1) / 2 - 1], 1);
                }
                else {
                    newS[(x + 1 + 9) / 2 - 1] = rotate(s[(x + 1 + 9) / 2 - 1], 1);
                }
            }

            if (dist.count(newS) == 0) {
                dist[newS] = dist[s] + 1;
                q.push(newS);
            }
        }
    }

    return 0;
}