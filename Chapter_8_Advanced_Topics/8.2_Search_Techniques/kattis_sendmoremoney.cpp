/**Kattis - sendmoremoney
 * Difficult (tedious) backtracking + pruning problem. The solution sounds easy, work from right
 * to left, assigning letters to digits (which ones are available are kept track of with a bit
 * mask), and if they have already been assigned, check that they are valid. The issue is the
 * implementation of this is extremely tedious with multiple cases (e.g. same letter, first letter
 * of a number, etc). It is hard to get nice looking code that works well across the cases.
 * I think my janky for loop with a lot of if else for the cases is at least decent...
 * 
 * Time: O(?), Space: O(?)
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

string w1, w2, w3;
inline int dat(char c) { return c - 'A'; }
vector<int> state, bestState;
bool found;
int used;
string s;
void backtrack(int i, int carry)
{
    if (i == (int)w3.size()) {
        if (state[dat(w3.back())] == 0 || state[dat(w1.back())] == 0 || state[dat(w2.back())] == 0)
            return;
        if (carry == 0) {
            if (found == false) {
                found = true;
                bestState = state;
            }
            else
                bestState = min(bestState, state);
        }
        return;
    }

    int lStart = 0, lEnd = 9;
    int mStart = 0, mEnd = 9;
    bool sameLet = (i < (int)w1.size() && i < (int)w2.size() && w1[i] == w2[i]);
    if (sameLet) {
        if (state[dat(w1[i])] != -1) {
            lStart = state[dat(w1[i])];
            lEnd = state[dat(w1[i])];
        }
        mStart = -1;
        mEnd = -1;
    }
    else {
        if (i >= (int)w1.size()) {
            lStart = 0;
            lEnd = 0;
        }
        else {
            if (state[dat(w1[i])] == -1) {
                lStart = 0;
            }
            else {
                lStart = state[dat(w1[i])];
                lEnd = state[dat(w1[i])];
            }
        }
        if (i >= (int)w2.size()) {
            mStart = 0;
            mEnd = 0;
        }
        else {
            if (state[dat(w2[i])] == -1) {
                mStart = 0;
            }
            else {
                mStart = state[dat(w2[i])];
                mEnd = state[dat(w2[i])];
            }
        }
    }
    for (int l = lStart; l <= lEnd; l++) {
        for (int m = mStart; m <= mEnd; m++) {
            if (i < (int)w1.size() && i < (int)w2.size() && l == m) continue;
            if (sameLet) {
                m = l;
            }
            int targ = (l + m + carry) % 10;
            bool setW1 = (i < (int)w1.size() && state[dat(w1[i])] == -1);
            if (setW1 && (used & (1 << l))) continue;
            if (setW1) {
                state[dat(w1[i])] = l;
                used |= (1 << l);
            }

            bool setW2 = (i < (int)w2.size() && state[dat(w2[i])] == -1);
            if (setW2 && (used & (1 << m))) {
                if (setW1) {
                    state[dat(w1[i])] = -1;
                    used &= ~(1 << l);
                }
                continue;
            }
            if (setW2) {
                state[dat(w2[i])] = m;
                used |= (1 << m);
            }

            if ((state[dat(w3[i])] != -1 && state[dat(w3[i])] != targ) ||
                (state[dat(w3[i])] == -1 && (used & (1 << targ)))) {
                if (setW1) {
                    state[dat(w1[i])] = -1;
                    used &= ~(1 << l);
                }
                if (setW2) {
                    state[dat(w2[i])] = -1;
                    used &= ~(1 << m);
                }
                continue;
            }
            bool setW3 = (state[dat(w3[i])] == -1);
            if (setW3) {
                state[dat(w3[i])] = targ;
                used |= (1 << targ);
            }

            backtrack(i + 1, (l + m + carry) / 10);

            if (setW1) {
                state[dat(w1[i])] = -1;
                used &= ~(1 << l);
            }
            if (setW2) {
                state[dat(w2[i])] = -1;
                used &= ~(1 << m);
            }
            if (setW3) {
                state[dat(w3[i])] = -1;
                used &= ~(1 << targ);
            }
            if (sameLet) break;
        }
    }
}
int main()
{
    fast_cin();
    used = 0;
    cin >> s;
    int cur = 0;
    while (s[cur] != '+') {
        w1 += s[cur];
        cur++;
    }
    cur++;
    while (s[cur] != '=') {
        w2 += s[cur];
        cur++;
    }
    cur++;
    while (cur < (int)s.size()) {
        w3 += s[cur];
        cur++;
    }
    reverse(w1.begin(), w1.end());
    reverse(w2.begin(), w2.end());
    reverse(w3.begin(), w3.end());
    state.assign(26, -1);

    found = false;

    if (w3.size() < max(w2.size(), w1.size())) {
        cout << "impossible" << endl;
        return 0;
    }
    backtrack(0, 0);
    assert(used == 0);

    if (!found) {
        cout << "impossible" << endl;
        return 0;
    }
    string ans = "";
    for (auto c : s) {
        if (c == '+' || c == '=')
            ans += c;
        else
            ans += (char)('0' + bestState[dat(c)]);
    }

    // This set of code is VERY useful to checking the properties of our solution.
    bool correspondence = true;
    for (int i = 0; i < (int)ans.size() && correspondence; i++) {
        for (int j = i; j < (int)ans.size() && correspondence; j++) {
            if (s[i] == s[j] && ans[i] != ans[j]) {
                correspondence = false;
            }
            else if (s[i] != s[j] && ans[i] == ans[j]) {
                correspondence = false;
            }
        }
    }
    assert(correspondence);

    int carry = 0;
    for (int i = 0; i < (int)w3.size(); i++) {
        int l = (i < (int)w1.size() ? bestState[dat(w1[i])] : 0);
        int m = (i < (int)w2.size() ? bestState[dat(w2[i])] : 0);
        int targ = (l + m + carry) % 10;
        carry = (l + m + carry) / 10;
        assert(targ == bestState[dat(w3[i])]);
    }
    cout << ans << endl;

    return 0;
}