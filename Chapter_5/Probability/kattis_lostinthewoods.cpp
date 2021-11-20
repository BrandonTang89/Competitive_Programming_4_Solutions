/**Kattis - lostinthewoods
 * An interesting problem I must say. The naive solution is to use dfs continuously, tracking the
 * length of the cur path and the probability, returning when the probability is lower than a
 * threshold. However, one must realise the overlapping subproblems. There are multiple paths of the
 * same length that end to at the same vertex. Instead of starting a separate DFS call from each of
 * those instances, we should combine their probabilities together and just start a single DFS call
 * with probabilty equal to their sum.. But how do we implement this?
 *
 * The answer is to process paths increasing length. We use a 2d vector that stores the probability
 * that a length i path ends at vertex j. However, noticing that we only need to use the values from
 * the previous row, we can just use the memory saving technique to only require 2 x 1d vector. So
 * in this case, for each vertex, we propagate its probability to the neighbours, except for the
 * last node where we add the probability * length to the answer. As the length l increases, the
 * total probability left in the network decreases exponentially since all the probability at n-1 is
 * removed. Past a certain point, our answer converges to the true value.
 *
 * Time: O((V + E) * ub), Space: O(V + E)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld EPS = 1e-9;

int n, e, u, v;
ld ans = 0;

vector<vector<int>> adjlist;
vector<ld> prob, prob_old;

int main() {
    scanf("%d %d", &n, &e);
    adjlist.assign(n, vector<int>());
    prob.assign(n, 0);

    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }
    int ub = 10000;
    prob[0] = 1;
    for (int l = 1; l < ub; l++) {
        prob_old = prob;
        prob.assign(n, 0);
        for (int i = 0; i < n - 1; i++) {
            for (int v : adjlist[i]) {
                prob[v] += prob_old[i] / adjlist[i].size();
            }
        }
        ans += prob[n - 1] * l;
        // printf("%d %.10Lf\n", l, prob[n-1]);
    }
    printf("%.10Lf\n", ans);

    return 0;
}