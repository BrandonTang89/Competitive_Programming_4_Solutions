/**Kattis - convoy
 * Not a super easy problem. Observe that once we move a car from start to end, the only reason to
 * ever move it back to the start is to use it immediately, else we can just use a car at the start!
 * Now, we have 2 priority queues, one for the people at the start and one for people at the end. If
 * we have cars at the start we can consider taking people from there, else we can only consider
 * taking people from the end (ofc if theres no one at the end yet, we can't do that).
 *
 * These priority queues store the time that the person will be able to transport people to the end
 * by, possibly going back to the start if needed as well as the time taken for a single pass from
 * start to end. We then consider the best candidate from each potential queue and pick the one
 * that finishes the job earlier and use that one. Then we update the queues. Note that we should
 * pick the slowest 4 people from the start queue. Since each element of the start queue is just
 * (time for single pass, time for single pass) then we can just take the last 4 elements from the
 * start queue as our passengers. Note that we don't need to actually update the end queue with the
 * passengers since the driver will be the one who drives back if needed (passengers actually
 * useless already).
 *
 * Its left an exercise to the reader to prove that this works :) but thats honestly not really
 * needed, just convinve yourself that it works before implementing. Also since we need both the
 * front and end of the priority queue and need to delete from it, we use a multiset rather than the
 * C++ priority queue.
 *
 * Time: O(n log n), Space: O(n)
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

int n, k;
multiset<pair<ll, ll>> pq_start, pq_end;  // time to get to / back to end, movement time
int main() {
    fast_cin();
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pq_start.insert({a, a});
    }

    ll ans = 0;
    while (pq_start.size() > 0) {
        int lowest = 1e9;
        bool new_car = false;
        if (pq_end.size() > 0) lowest = (*pq_end.begin()).first;
        if (k > 0) {
            auto [a, b] = *pq_start.begin();
            if (a < lowest) {
                new_car = true;
            }
        }

        if (new_car) {
            auto [t_back, t_trav] = *pq_start.begin();
            pq_end.insert({t_back + 2 * t_trav, t_trav});

            ans = max(ans, t_back);
            pq_start.erase(pq_start.begin());
            k--;

            // delete last 4 in start
            for (int i = 0; i < 4; i++) {
                if (pq_start.size() > 0) pq_start.erase(--(pq_start.end()));
            }
        }

        else {
            auto [t_back, t_trav] = *pq_end.begin();
            pq_end.insert({t_back + 2 * t_trav, t_trav});
            ans = max(ans, t_back);

            pq_end.erase(pq_end.begin());

            // delete last 4 in start
            for (int i = 0; i < 4; i++) {
                if (pq_start.size() > 0) pq_start.erase(--(pq_start.end()));
            }
        }
    }
    cout << ans << endl;

    return 0;
}