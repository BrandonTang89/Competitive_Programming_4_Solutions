/**Kattis - subexpression
 * This was a very difficult question for me. The most difficulty part was the fact that using
 * strings as keys for the binary heap resulted in MLE while storing indices as our keys results in
 * TLE due to the need to check if a key in the heap corresponds to the same node as we are
 * processing.
 *
 * The eventual trick I came across was to use a hash table of std::string_view as a key. This is
 * because all our keys are substrings of x, so there are (enourmously) many overlaps, using
 * string view allows us to reference just our 1 copy of x for all the keys, preventing MLE.
 * 
 * Apart from this trick, everything else is relatively as per usual. Perhaps some other micro
 * optimisations include.
 * 1. Only storing a string view if we could use it again, ie if its size is smaller than the remaining
 *    length after its end.
 * 2. Doing the nesting counting only once at the start rather than for each call of parse.
 * 
 * Time: O(n^2), Space: O(n) where n is the length of x.
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

int counter = 0;
string x, ans;
unordered_map<string_view, int> m;
vector<int> nesting_level;

void parse(int st, int en) {
    string_view v = string_view(x).substr(st, en - st + 1);
    if (m.find(v) != m.end()) {
        ans += to_string(m[v]);
        return;
    }
    if ((en - st + 1) < (int)x.size() - en - 1) {
        m[v] = counter;
    }
    counter++;
    if (x[en] != ')') {
        ans += v;
        return;
    }

    int end_of_op = 0;
    for (int i = st; i <= en; i++) {
        if (nesting_level[i] == nesting_level[st] + 1) {
            if (x[i] == '(') {
                end_of_op = i - 1;
            } else if (x[i] == ',') {
                ans += x.substr(st, -st + end_of_op + 1) + "(";
                parse(end_of_op + 2, i - 1);
                ans += ",";
                parse(i + 1, en - 1);
                ans += ")";
                return;
            }
        }
    }
}
int main() {
    fast_cin();
    int c;
    cin >> c;
    for (int i = 0; i < c; i++) {
        cin >> x;
        counter = 1;
        m.clear();
        ans = "";
        nesting_level.assign(x.size(), 0);
        for (int i = 0; i < (int)x.size(); i++) {
            if (x[i] == '(') {
                nesting_level[i] = nesting_level[i - 1] + 1;
            } else if (x[i] == ')') {
                nesting_level[i] = nesting_level[i - 1] - 1;
            } else {
                nesting_level[i] = nesting_level[i - 1];
            }
        }

        parse(0, x.size() - 1);
        cout << ans << endl;
    }

    return 0;
}