/**Kattis - cardhand
 * Complete search + longest increasing subsequence.
 * The complete search is clear. We just try all possible permutations of suits and all 2^4
 * possiblities of sorting by increasing or decreasing order for each suit. The actual sorting is
 * tricky, we actually have seen this before somewhere (a long time ago) where the optimal method is
 * moving all the stuff not in the longest increasing subsequence. This is because all the stuff
 * between 2 elements of an increasing subsequence need to be moved. So we need to move n -
 * lis.size() cards.
 *
 * Time: O(2^4 * 4! * n * log(n))
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
vector<string> cards[4][2];
vector<string> hand;
vector<string> target;

int toRank(string card)
{
    if (card[0] == 'A') return 14;
    if (card[0] == 'K') return 13;
    if (card[0] == 'Q') return 12;
    if (card[0] == 'J') return 11;
    if (card[0] == 'T') return 10;
    return card[0] - '0';
}
bool comp(string a, string b) { return toRank(a) < toRank(b); }
int main()
{
    fast_cin();
    cin >> n;
    hand.resize(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        hand[i] = s;

        switch (s[1]) {
            case 's':
                cards[0][0].push_back(s);
                break;
            case 'h':
                cards[1][0].push_back(s);
                break;
            case 'd':
                cards[2][0].push_back(s);
                break;
            case 'c':
                cards[3][0].push_back(s);
                break;
            default:
                assert(false);
                break;
        }
    }
    for (int i = 0; i < 4; i++) {
        sort(cards[i][0].begin(), cards[i][0].end(), comp);  // increasing
        cards[i][1] = cards[i][0];
        reverse(cards[i][1].begin(), cards[i][1].end());  // decreasing
    }

    vector<int> perms = {0, 1, 2, 3};
    int ans = 1e6;
    do {
        for (int bm = 0; bm < (1 << 4); bm++) {
            // bm & (1 << i) is true if we sort suit i in reverse (or 0 otherwise)
            target.clear();
            for (auto suit : perms) {
                if (bm & (1 << suit)) {
                    for (auto card : cards[suit][1]) {
                        target.push_back(card);
                    }
                }
                else {
                    for (auto card : cards[suit][0]) {
                        target.push_back(card);
                    }
                }
            }
            assert((int)target.size() == n);
            unordered_map<string, int> index;
            for (int i = 0; i < n; i++) {
                index[target[i]] = i;
            }
            vector<int> ihand(n);
            for (int i = 0; i < n; i++) {
                ihand[i] = index[hand[i]];
            }
            // calculate the longest increasing subsequence
            vector<int> lis;
            for (int i = 0; i < n; i++) {
                auto it = lower_bound(lis.begin(), lis.end(), ihand[i]);
                if (it == lis.end()) {
                    lis.push_back(ihand[i]);
                }
                else {
                    *it = ihand[i];
                }
            }
            int dist = n - (int)lis.size();
            ans = min(ans, dist);
        }
    } while (next_permutation(perms.begin(), perms.end()));
    cout << ans << endl;
    return 0;
}