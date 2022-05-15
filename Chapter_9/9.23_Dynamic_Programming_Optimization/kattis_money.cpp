/**Kattis - money
 * Divide and Conquer. Effectively you are given 2 sets of points, u want to find the
 * maximum of (ix - jx)*(iy - jy) for all pairs of i in the first set and j in the second set.
 *
 * First we note that some producers and consumers are completely useless. For a given
 * producer, if we can find on with a <= cost that starts at least as early, then that
 * producer is useless. Similarly, if we find a consumer that pays at least as much
 * as my consumer and ends at least as late as it, my consumer is useless. We can sort
 * and filter off these useless producers and consumers. (Note that we don't actually
 * have to write the custom comparators, just sort by the default less or greater)
 *
 * Then we try to find the optimal consumer given that we use the middle producer. If we can find
 * one, then all producers to the left of it will only need to consider consumers from 0 until the
 * optimal producer, all producers to the right of it will only need to consider consumers from the
 * optimal producer until the end. (this is provable by some drawings on pen and paper).
 * Then we can recurse into subproblems of dealing with the producers on the left and the right
 * of the middle consumer. We take the max of the using the middle producer, using one on the
 * left and using one on the right.
 *
 * regarding what happens if we cannot find any optimal answer for the middle producer, ie none of
 * the consumer are to the upper right of the middle producer, we can just still split the consumers
 * such that the total number of consumer considered by the left and right of the middle producer is
 * not more than n+1, refer to how I manipulate the max_index below.
 *
 * Time: O(n log m), Space: O(n + m)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int np, nc;
vector<pair<ll, ll>> producers, consumers;  // (date, amt)
vector<pair<ll, ll>> conf, prof;  // consumers and producers filtered
ll dnc(ll prol, ll pror, ll conl, ll conr) {
    if (prol > pror) return 0;
    if (conl > conr) return 0;

    ll mid = (prol + pror) / 2;
    ll cur_max = 0;
    ll max_index = conl;

    for (ll i = conl; i <= conr; i++) {
        if (conf[i].first <= prof[mid].first) {
            max_index = min(conr, i + 1);  // in case later on no possible matches
            continue;
        }
        if (conf[i].second <= prof[mid].second) {  // none of the subseqent can be used
            break;
        }

        ll cur = (conf[i].first - prof[mid].first) * (conf[i].second - prof[mid].second);
        if (cur >= cur_max) {
            cur_max = cur;
            max_index = i;
        }
    }
    return max(max(dnc(prol, mid - 1, conl, max_index), dnc(mid + 1, pror, max_index, conr)),
               cur_max);
}
int main() {
    cin >> np >> nc;
    for (ll i = 0; i < np; i++) {
        ll p, d;
        cin >> p >> d;
        producers.push_back({d, p});
    }
    for (ll i = 0; i < nc; i++) {
        ll q, e;
        cin >> q >> e;
        consumers.push_back({e, q});
    }
    sort(producers.begin(), producers.end()); // sort increasing date, increasing amt
    sort(consumers.begin(), consumers.end(), greater<pair<ll, ll>>()); // sort decreasing date, decreasing amt

    prof.push_back(producers[0]);
    for (ll i = 1; i < np; i++) {
        if (producers[i].first == prof.back().first) {
            continue;
        }
        if (producers[i].second >= prof.back().second) {
            continue;
        }
        prof.push_back({producers[i].first, producers[i].second});
    }
    conf.push_back(consumers[0]);
    for (ll i = 1; i < nc; i++) {
        if (consumers[i].first == conf.back().first) {
            continue;
        }
        if (consumers[i].second <= conf.back().second) {
            continue;
        }
        conf.push_back({consumers[i].first, consumers[i].second});
    }
    reverse(conf.begin(), conf.end());  // all sort by increasing date
    cout << dnc(0, prof.size() - 1, 0, conf.size() - 1) << endl;
    return 0;
}