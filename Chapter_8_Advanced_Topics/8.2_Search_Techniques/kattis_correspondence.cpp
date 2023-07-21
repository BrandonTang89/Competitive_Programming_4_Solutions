/**Kattis - correspondence
 * Backtracking with pruning. Despite the high difficulty on Kattis, this problem really isn't too
 * bad. The idea is very straightforward, do something equivalent to a n! backtracking brute force.
 * We of course use a bitmask to represent the indices that haven't been used yet. To represent the
 * current values of the words (and the best sequence thus far) we opt to use a vector of string
 * views, allowing for O(1) insertion and deletion from the back. It is only when comparing that we
 * will take a long time to do (but this is unavoidable unless we do some fancy hashing thing). We
 * avoid having to compare too frequently by keeping track of the lengths of both words and only
 * compare when the lengths are actually the same.
 * 
 * Time: O(n! * n*100), Space: O(n*100)
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
vector<pair<string, string>> words;
vector<string_view> w1, w2, bestSeq;
int w1Length, w2Length, bestLen;

void backtrack(int bm)
{
    if (bm != (1 << n) - 1 && w1Length == w2Length) {
        // check that w1 and w2 are equal
        int i = 0, w1Cur = 0;
        int j = 0, w2Cur = 0;
        int same = true;
        for (int compared = 0; compared < w1Length; compared++) {
            if (w1[w1Cur][i] != w2[w2Cur][j]) {
                same = false;
                break;
            }
            i++;
            j++;
            if (i == (int)w1[w1Cur].size()) {
                i = 0;
                w1Cur++;
            }
            if (j == (int)w2[w2Cur].size()) {
                j = 0;
                w2Cur++;
            }
        }

        if (same) {
            if (w1Length < bestLen) {
                bestLen = w1Length;
                bestSeq = w1;
            }
            else if (w1Length == bestLen) {
                // get the lexicographically smallest
                int i = 0, w1Cur = 0;
                int j = 0, bestCur = 0;
                for (int compared = 0; compared < w1Length; compared++) {
                    if (w1[w1Cur][i] < bestSeq[bestCur][j]) {
                        // new smallest
                        bestSeq = w1;
                        break;
                    }
                    else if (w1[w1Cur][i] > bestSeq[bestCur][j]) {
                        // not smallest
                        break;
                    }
                    i++;
                    j++;
                    if (i == (int)w1[w1Cur].size()) {
                        i = 0;
                        w1Cur++;
                    }
                    if (j == (int)bestSeq[bestCur].size()) {
                        j = 0;
                        bestCur++;
                    }
                }
            }
        }
    }
    if (bm == 0) return;

    int mask = bm;
    while (mask) {
        int next = __builtin_ctz(mask);

        w1.emplace_back(words[next].first);
        w2.emplace_back(words[next].second);
        w1Length += words[next].first.size();
        w2Length += words[next].second.size();

        backtrack(bm ^ (1 << next));

        w1.pop_back();
        w2.pop_back();
        w1Length -= words[next].first.size();
        w2Length -= words[next].second.size();

        mask ^= (1 << next);
    }
}
int main()
{
    fast_cin();
    int tc = 0;
    while (cin >> n) {
        tc++;
        words.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> words[i].first >> words[i].second;
        }
        bestLen = 1e9;
        backtrack((1 << n) - 1);

        cout << "Case " << tc << ": ";
        if (bestLen == 1e9) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            for (auto c : bestSeq) cout << c;
            cout << endl;
        }
    }

    return 0;
}