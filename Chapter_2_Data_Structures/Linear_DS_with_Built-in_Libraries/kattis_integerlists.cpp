/**Kattis - integerlists
 * We just maintain a deque of integers (or strings) and pop from front or back depending on whether
 * the current list is "reversed" or not. At the end of the commands, if the list is reversed,
 * we just reverse it.
 * 
 * Take note of the edge case of empty input or output list!
 * 
 * Time: O(len(commands) + len(s)), Space: O(len(s) + len(commands))
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

int num_tc, n;
string cur_num = "", s, commands;
deque<string> dq;
int main() {
    fast_cin();
    cin >> num_tc;
    for (int tc = 0; tc < num_tc; tc++) {
        dq.clear();
        cin >> commands >> n;
        cin >> s;
        if (n > 0) {
            for (int i = 1; i < (int)s.size(); i++) {
                if (s[i] == ',' || s[i] == ']') {
                    dq.push_back(cur_num);
                    cur_num = "";
                } else
                    cur_num += s[i];
            }
        }

        bool reversed = false;
        bool error = false;
        for (auto c : commands) {
            if (c == 'R') {
                reversed = !reversed;
            } else {
                if (dq.size() == 0) {
                    cout << "error" << endl;
                    error = true;
                    break;

                } else if (not reversed) {
                    dq.pop_front();
                } else {
                    dq.pop_back();
                }
            }
        }
        if (!error) {
            if (reversed) {
                reverse(dq.begin(), dq.end());
            }
            string ans = "[";
            for (auto i : dq) {
                ans += i + ",";
            }
            if ((int)dq.size() > 0) {
                ans.pop_back();
            }
            ans += "]";
            cout << ans << endl;
        }
    }

    return 0;
}