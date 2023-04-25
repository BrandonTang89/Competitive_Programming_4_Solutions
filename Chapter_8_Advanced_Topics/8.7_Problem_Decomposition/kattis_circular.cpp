/**Kattis - circular
 * Rather adhoc + some hash tables. We essentially have a bunch of different parentheses sequences
 * and want to find a cutting that maximises the number of valid bracketing sequences.
 *
 * Observe that if we keep track of a counter of the number of "open brackets left" for each
 * sequence, we can easily filter out sequences that don't even have the same number of open and
 * close brackets. But furthermore, for sequences that num '(' == num ')', if we cut the sequence
 * immediately after where the counter becomes the minimum value (could occur at multiple places)
 * then this sequence is valid.
 *
 * Knowing the minimum counter value for each sequence, we can then find out the set of cuts that
 * allows that sequence to be valid. We now need to figure out which cut will maximise the number of
 * valid sequences. Observe that we can use the technique of recording changes in the number of
 * valid sequences if we cut at index i. I.e. difference of +1 if a sequence gets to its minimum,
 * and -1 if a sequence leaves its minimum. At each index, there will only be at most 1 change in
 * the difference (except index 0 which will have to account for sequences that have a minimum of
 * 0).
 *
 * The last issue is that we want the smallest cut that maximises the number of valid sequences, but
 * the number of a cut for the question refers to the index immediately after the cut where as the
 * methods described above were written to label the cut with index of the element immediately
 * before the cut. Annoyingly, this means we need to rotate the entire array by moving the last
 * element to the front... Ugly but it works.
 *
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> v;
vector<pair<int, int>> arr;
vector<pair<char, int>> ori;
unordered_map<int, int> counter, mini;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        int a;
        cin >> c >> a;
        ori.push_back({c, a});
    }
    for (int i = 0; i < n; i++) {
        auto [c, a] = ori[(n - 1 + i) % n];  // rotate array
        if (c == 's') {
            arr.push_back({0, a});
            counter[a]++;
        }
        else {
            arr.push_back({1, a});
            counter[a]--;
            mini[a] = min(mini[a], counter[a]);
        }
    }

    for (auto &[a, c] : counter) {
        if (c != 0) {
            mini[a] = 1e9;  // ignore these, not the same number of open and close
        }
    }
    counter.clear();
    v.assign(n, 0);
    int ans = 0, cur = 0, bestidx = 0;
    for (auto &[a, c] : mini) { // edge case of sequences with mini = 0
        if (c == 0) {
            v[0]++;
        }
    }
    for (int i = 0; i < n; i++) {
        auto [t, a] = arr[i];
        if (t == 0) {
            if (counter[a] == mini[a]) {
                v[i] -= 1;
            }
            counter[a]++;  // went out of the minimum
        }
        else {
            counter[a]--;
            if (counter[a] == mini[a]) {  // just became small enough
                v[i] += 1;
            }
        }
        cur += v[i];
        if (ans < cur) {
            ans = cur;
            bestidx = i;
        }
    }

    cout << (bestidx + 1 == n ? n : (bestidx + 1) % n) << " " << ans << endl;
    return 0;
}