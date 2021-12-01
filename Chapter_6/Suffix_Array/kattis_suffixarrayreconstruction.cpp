/**Kattis - suffixarrayreconstruction
 * I have found the most annoying bug I ever had. My problem was that I broke from the loop
 * for (int i = 0; i < num_suffix; i++) if it was impossible. While this would keep the correct
 * answer for the current word, it would leave the excess suffixes in the input stream... leading to
 * wrong answers later on. Also this question was very unclear and what not, overall i would say its
 * not very good. 
 * 
 * Time: O(total number of chars), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int num_tc;
int n, num_suffix, pos;
string suffix;
vector<char> word;
int main() {
    cin >> num_tc;
    for (int tc = 0; tc < num_tc; tc++) {
        cin >> n >> num_suffix;
        word.assign(n, '-');
        bool impossible = false;
        for (int i = 0; i < num_suffix; i++) {
            cin >> pos >> suffix;
            pos--;

            bool contains_wildcard = false;
            for (int p = pos; p < pos + (int)suffix.size(); p++) {
                if (suffix[p - pos] == '*') {
                    contains_wildcard = true;
                    break;
                }
                if (word[p] != '-' && word[p] != suffix[p - pos]) {
                    impossible = true;
                    break;
                }
                word[p] = suffix[p - pos];
            }
            if (contains_wildcard) {
                for (int p = n - 1; p >= pos; p--) {
                    if (suffix[p - n + suffix.size()] == '*') {
                        break;
                    }
                    if (word[p] != '-' && word[p] != suffix[p - n + suffix.size()]) {
                        impossible = true;
                        break;
                    }
                    word[p] = suffix[p - n + suffix.size()];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (word[i] == '-') {
                impossible = true;
                break;
            }
        }

        if (impossible) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            for (int i = 0; i < n; i++) {
                cout << word[i];
            }
            cout << endl;
        }
    }

    return 0;
}