/**Kattis - anotherdice
 * Quite a non-trivial probabilty with DP problem. The main idea is to compute the probability of
 * reaching n given that we have diceLeft dice that we can roll and that we can still call all the
 * numbers that are 1 in the bitmask (with worm being the LSB, 1 being 2nd-LSB, 5 being MSB).
 *
 * The tricky part is the transition. The transition is done by considering all possible
 * distributions of numbers on the dice (e.g. 1 worm, 2 '2's, 5 '4's) and then taking the max of the
 * probability of winning given we select each number from worm to 5 to remove. The transition
 * formed by distributing diceLeft dice into 6 bucks [worm..5] is naturally recursive and so we move
 * the transition function into a separate function. However, this transition function needs to hold
 * on to certain state across transitions (e.g. the accumulator that adds up the probabilities for
 * each distribution). We can't just use a global variable since the transition function will call
 * the DP function (in a mutually recursive way) since that will reset that global variable, as such
 * we use a stack for each state that we need to hold on to. We push and pop the relevant state that
 * the transition function needs to hold on to within the DP function.
 *
 * In theory we could just put some of the state stuff into the transition function.. But that would
 * only work for things that don't change (n, bm, dls) so at some point we would need a stack anyway
 * (acc, arrs, factors).
 *
 * Time: O(n*8*2^6 * (8+5 C 5)), Space: O(n*8*2^6)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define double long double
double factorial(int n)
{
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

double memo[41][9][1 << 6];
double dp(int n, int diceLeft, int bm);
double acc = 0, initDiceLeft;
vector<double> accs, factors;
vector<int> ns, bms, dls;
vector<vector<int>> arrs;
void transition(int diceLeft, int cur)
{
    if (cur == 6) {
        int m = bms.back();
        double ans = 0;
        while (m) {
            int selected = __builtin_ctz(m);
            m -= (1 << selected);
            if (arrs.back()[selected] == 0) continue;

            // we select arr[selected] dice
            int amount = (selected == 0) ? 5 : selected;
            ans = max(ans, dp(ns.back() - arrs.back()[selected] * amount,
                              dls.back() - arrs.back()[selected], bms.back() ^ (1 << selected)));
        }
        accs.back() += ans * factors.back();
        return;
    }
    if (cur == 5) {  // last number
        factors.back() /= factorial(diceLeft);
        arrs.back()[cur] = diceLeft;
        transition(0, cur + 1);
        factors.back() *= factorial(diceLeft);
        return;
    }
    for (int j = 0; j <= diceLeft; j++) {  // j dice show cur
        factors.back() /= factorial(j);
        arrs.back()[cur] = j;
        transition(diceLeft - j, cur + 1);
        factors.back() *= factorial(j);
    }
}
double dp(int n, int diceLeft, int bm)
{
    if (n < 0) return dp(0, diceLeft, bm);  // finished but no worm
    if (n == 0 && (bm & 1) == 0) return 1;  // finished and have taken worm
    if (diceLeft == 0) return 0;            // no more dice

    if (memo[n][diceLeft][bm] != -1) return memo[n][diceLeft][bm];

    // roll the dice...
    factors.push_back(pow((1.0 / 6.0), diceLeft) * factorial(diceLeft));
    acc = 0;
    dls.push_back(diceLeft);
    ns.push_back(n);
    bms.push_back(bm);
    accs.push_back(0);
    arrs.push_back(vector<int>(6, 0));
    transition(diceLeft, 0);
    double ans = accs.back();
    dls.pop_back();
    ns.pop_back();
    bms.pop_back();
    factors.pop_back();
    arrs.pop_back();
    accs.pop_back();
    return memo[n][diceLeft][bm] = ans;
}

int main()
{
    int tc;
    cin >> tc;
    cout << setprecision(12) << fixed;
    while (tc--) {
        int n;
        cin >> n;
        memset(memo, -1, sizeof memo);
        cout << dp(n, 8, (1 << 6) - 1) << endl;
        assert((int)dls.size() == 0);
        assert((int)ns.size() == 0);
        assert((int)bms.size() == 0);
        assert((int)factors.size() == 0);
        assert((int)accs.size() == 0);
        assert((int)arrs.size() == 0);
    }

    return 0;
}