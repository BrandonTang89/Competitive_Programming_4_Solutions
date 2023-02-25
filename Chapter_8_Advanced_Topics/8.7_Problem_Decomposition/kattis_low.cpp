/**Kattis - low
 * BSTA + Greedy. We binary search for the minimum difference between the chips that can be
 * attained. The greedy part is about deciding if we can attain such a difference.
 *
 * Observation 1: If we select some set of batteries as the minimum in the chips, the first 2
 * batteries will go to the first machine, the next 2 to the second machine, and so on. This
 * minimises the difference
 *
 * Observation 2: The optimal selected set of batteries as a minimum will contain adjacent pairs. If
 * we do a pairing that is not adjacent, we can get a better (not worse) arrangement by pairing the
 * smaller of the 2 battries with the next larger battery (from the smaller one) since this will
 * also be valid and we will be able to use more batteries to make other pairings.
 *
 * Initially, observe that the lowest valued battery will need to be a minimum in some chip. Observe
 * that we should just put the second lowest battery in other chip in the same machine if possible.
 * If this is not possible, we alr failed. This is because all other batteries will be at least as
 * large as the second smallest battery, so we cannot make the difference smaller.
 *
 * Now suppose we have done this for the first 2 chips, we try to find another pair of batteries
 * that will be the next minimum. We can check for the next pair of adjacent batteries that are
 * within the difference we are trying to attain.
 *
 * We fail to do this when we run out of "reserve" battery placings which are battery placings that
 * can house batteries which are not the minimum in any chip. So we need to select the second
 * pairing before we run out of reserve battery placings from the first pair. We need to select the
 * third pairing before we run out of reserve battery placings from the first 2 pairings, etc. We
 * should greedily select the first valid pairing so we maximise the number of reserve battery
 * placings we have to use for subsequent pairings.
 *
 * We carry on doing this until we have made all the pairings or we run out of reverse battery
 * placings at some point. To ensure the first pair isn't a special case, we just initialise the
 * reserve to be 0 so we have to use the first pair.
 * 
 * Time: O(nklog(10^9)), Mem: O(nk)
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

int n, k;
vector<int> v;
bool check(int x)
{  // can we attain a difference between chips of at most x?
    int reserve = 0;
    int cur = 0;
    int done = 0;
    while (cur < 2 * n * k - 1) {
        if (v[cur + 1] - v[cur] <= x) {
            reserve += 2 * (k - 1);
            cur += 2;
            done++;
            if (done == n) return true;
        }
        else {
            reserve -= 1;
            cur += 1;
            if (reserve < 0) {  // we failed
                return false;
            }
        }
    }

    assert(false);
}
int main()
{
    fast_cin();
    cin >> n >> k;
    v.resize(2 * n * k);
    for (int i = 0; i < 2 * n * k; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    int l = 0, r = v[2 * n * k - 1] - v[0];
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    cout << l << endl;
    return 0;
}