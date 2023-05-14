/**Kattis - weather
 * Math + Greedy + Complete Search + Data Structures. We first recognise this as a "standard"
 * problem of constructing a binary tree with 4^n nodes where the total cost of the tree is
 * minimised. The cost of a tree is defined as the sum of the products of the probabilities of each
 * node and the depth of the node. It is "well known" that the optimal strategy is to repeatedly
 * merge the two smallest nodes into a new subtree (or better represented as a node) with
 * probability equal to the sum of the probabilities of the two subtrees. This sum is added to the
 * total penalty. This is usually carried out with a simple priority queue. The optimality can be
 * seen by the fact that this produces a tree with the property: the sum of the subtree at any depth
 * is lower than the sum of any subtree with shallower depth. If this property is not satisfied, we
 * can always swap the 2 subtrees to attain a lower cost.
 *
 * However, the number of states is 4^n which will TLE for sure. But we notice that a lot of the 4^n
 * nodes actually have the same probablity... So what we can do is only put 1 copy of the
 * probability into the priority. Then when we take out the minimum node, we see if we have >= 2
 * copies of it, if so, we merge half of them with the other half. If not, we take out the second
 * minimum node and merge it with the minimum node. This way, every node in the priority queue will
 * be processed at most twice (though new nodes may be added).
 *
 * The last issue is how to calculate the initial probabilities and the number of copies of each.
 * We can do a recursive complete search to divide n into 4 groups. Then we for each n, we use
 * standard probability theory to calculate the probability of each group. The number of ways to
 * divide n into 4 groups (which is also the complexity of the complete search) is (n+3)C3 <= 1771,
 * surprisingly small compared to 4^20.
 *
 * The time and space complexity becomes quite difficult to compute... But its clearly quite fast
 * Time: O(?), Space: O(?)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
int n;
vector<int> amts;
ld probs[4];
unordered_map<ld, ll> numProb;
priority_queue<ld, vector<ld>, greater<ld>> pq;

ll factorials[21];
void search(int t, int left)
{
    if (t == 4) {
        ld prob = 1;
        for (int i = 0; i < 4; i++) {
            prob *= pow(probs[i], amts[i]);
        }
        ll num = factorials[n] / (factorials[amts[0]] * factorials[amts[1]] * factorials[amts[2]] *
                                  factorials[amts[3]]);
        numProb[prob] += num;
        return;
    }
    if (t == 3) {
        amts[t] = left;
        search(t + 1, 0);
        return;
    }
    for (int i = 0; i <= left; i++) {
        // take i of type t
        amts[t] = i;
        search(t + 1, left - i);
    }
}
int main()
{
    cin >> n;
    amts.resize(4);
    for (int i = 0; i < 4; i++) {
        cin >> probs[i];
    }
    factorials[0] = 1;
    for (int i = 1; i <= 20; i++) {
        factorials[i] = factorials[i - 1] * i;
    }

    search(0, n);

    for (auto it = numProb.begin(); it != numProb.end(); it++) {
        pq.push(it->first);
    }

    ld ans = 0;
    while (!pq.empty()) {
        ld f = pq.top();
        pq.pop();

        if (numProb[f] > 1) {
            ll num_take = numProb[f] / 2LL;
            ans += 2 * f * num_take;

            numProb[f] -= 2 * num_take;
            if (numProb[f] > 0) {
                pq.push(f);
            }
            if (numProb[2 * f] == 0) {
                pq.push(2 * f);
            }
            numProb[2 * f] += num_take;
            continue;
        }
        if (pq.empty()) {
            assert(fabs(f - 1.0) < 1e-12);
            break;
        }

        ld s = pq.top();
        pq.pop();

        ans += (f + s);
        if (numProb[f + s] == 0) {
            pq.push(f + s);
        }
        numProb[f] -= 1;
        numProb[s] -= 1;
        numProb[f + s] += 1;
        if (numProb[f] > 0) {
            pq.push(f);
        }
        if (numProb[s] > 0) {
            pq.push(s);
        }
    }
    cout << fixed << setprecision(10) << ans << endl;

    return 0;
}