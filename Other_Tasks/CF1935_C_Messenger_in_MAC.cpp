/** CF1935C
 * Greedy sorting + BSTA + sliding window with a max heap.
 *
 * Clearly for any fixed set of messages selected, the optimal way to arrange them is in
 * non-decreasing b_i (simple greedy exchange argument proof)
 * Doing this leads to the b_i terms telescoping to just b_j - b_i where b_j is the largest of the b
 * values amongst the message selected and b_i is the smallest
 * As such, we choose to sort the messages in non-decreasing b_i (will be helpful later)
 *
 * Now, in our BSTA, we are asking "is it possible to send k messages"
 *
 * To do this, We find min(mincost(i, j) across all i, j) where mincost(i, j) is the minimum cost of
 * taking k elements, including i and j, from the interval [i..j]. \
 * If min(mincost(i, j) across all i, j) <= l, then it is possible to send k messages.
 *
 * Consider some set S of k elements from the interval [i..j], where {i,j} subset S.
 * We have cost(S, i, j) = sum({a_q | q in S}) + b_j - b_i
 * And mincost(i, j) = min(cost(S, i, j) | S is a set of k elements from [i..j] containing i and j)
 *
 * We let S*(i, j) be argmin S of cost(S, i, j), i.e. the optimal set of k elements from [i..j]
 * with both i and j.
 *
 * Calculating S*(i, j) directly (via greedily selecting the k-2 elements with the smallest a_q values) 
 * will TLE but fortunately we can use the sliding window tactic.
 *
 * Fix i. We will efficiently iterate over S(i, j) as follows:
 * For j = i+k-1, we need to take all elements i, i+1, ..., i+k-1
 *  i.e. S*(i, j) = {i, i+1, ..., i+k-1}
 * For j > i+k-1, we observe
 *  S*(i, j) = S*(i, j-1) - {q in S*(i, j-1) | a_q is the largest amongst S*(i, j-1) } + {j}
 *
 * Using a max heap containing S*(i, j)\{i} and a sum variable, we can calculate mincost(i, j) in
 * O(log k) time (for most i, j).
 *
 * Simply iterating over all i and performing the above makes each call of possible(k) take
 * O(n^2 log k) time.
 *
 * Together with the BSTA, this means that the overall complexity is:
 *
 * Time: O(n^2 log^2 n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, l;
vector<pair<int, int>> msg;  // msg[i] = (a_i, b_i)

bool possible(int k)
{
    if (k == 0) return true;
    if (k == 1) {
        for (int j = 0; j < n; j++) {
            if (msg[j].first <= l) return true;
        }
        return false;
    }

    // We find min( cost(i, j) ) where cost(i, j) is the minimum cost of taking k elements,
    // including i and j

    priority_queue<int, vector<int>> pq;   // max heap, storing the values of the ais
    for (int i = 0; i < n + 1 - k; i++) {  // ensure within bounds
        while (!pq.empty()) pq.pop();
        ll sum = msg[i].first;                 // always included
        for (int j = i + 1; j < i + k; j++) {  // initialise the pq with the smallest k-1 elements
                                               // from i, i is already included
            pq.push(msg[j].first);
            sum += msg[j].first;
        }

        if (sum + msg[i + k - 1].second - msg[i].second <= l)
            return true;  // this might be the best solution

        for (int j = i + k; j < n; j++) {
            // We remove the highest cost element
            sum -= pq.top();
            pq.pop();

            // We add the new element
            pq.push(msg[j].first);
            sum += msg[j].first;

            if (sum + msg[j].second - msg[i].second <= l) return true;
        }
    }

    return false;
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> l;

        msg.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> msg[i].second >> msg[i].first;
        }
        sort(msg.begin(), msg.end());  // sort by increasing b_i
        for (int i = 0; i < n; i++) swap(msg[i].first, msg[i].second);

        // BSTA for the largest possible number of messages
        int le = 0, ri = n;
        while (le < ri) {
            int mid = (le + ri + 1) / 2;
            if (possible(mid)) {
                le = mid;
            }
            else {
                ri = mid - 1;
            }
        }

        // while (possible(le)) le++;
        // le--;

        cout << le << endl;
    }

    return 0;
}
