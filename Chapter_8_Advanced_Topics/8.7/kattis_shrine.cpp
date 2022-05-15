/**Kattis - shrine
 * Quite a difficult / tedious question I must say. The first part is determining a formula for the
 * cord length using the cosine rule. Then we need to determine the shrine locations. Both of these
 * are pretty easy. The difficult part comes in the complete search + BSTA + greedy line sweep
 * section. Study the code of the line sweep well, it was not exactly easy to synthesize. Note that
 * our complete search needs to be somewhat smart, we can't afford to check all num_shrine starting
 * positions for the first shrine position. Due to the symmetry of the problem (i think lol),
 * we can just assume that the first shrine is within the first num_shrines/w shrines. This is
 * very handwavy and might actually be a scam. But ya.
 * 
 * Time: O(n/w * 20), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, w, d;
vector<bool> isshrine;
vector<int> shrines;
ld PI = acos(-1);
ld cord_length(int i, int j) {
    if (i > j) swap(i, j);  // i <= j after this
    ld theta = (2 * PI / (ld)n) * (j - i);
    if (theta > PI) theta = 2 * PI - theta;
    return 1414.213562373095 * sqrt((ld)1 - cos(theta));
}

int main() {
    while (1) {
        cin >> w;
        if (w == 0) break;
        cin >> n >> d;
        isshrine.assign(n, false);
        shrines.clear();
        for (int i = 0; i < d; i++) {
            int divisor;
            cin >> divisor;
            for (int j = 0; j < n; j += divisor) {
                isshrine[j] = true;
            }
        }
        for (int i = 0; i < n; i++) {
            if (isshrine[i]) {
                shrines.push_back(i);
            }
        }
        int num_shrines = shrines.size();

        ld lowest_dist = 2000 * PI;
        for (int fst_s_idx = 0; fst_s_idx < num_shrines/w + 1; fst_s_idx++) {
            ld lo = 0, hi = 2000 * PI;  // we add the constant of 2 to go to and from center later
            for (int ite = 0; ite < 20; ite++) {
                ld mid = (lo + hi) / 2;

                int cur_idx = fst_s_idx, next_idx = (fst_s_idx + 1) % num_shrines;
                int num_workers_used = 1;
                ld cur_dist = 0;
                bool valid = true;
                while (next_idx != fst_s_idx) {
                    ld next_length = cord_length(shrines[cur_idx], shrines[next_idx]);
                    if (cur_dist + next_length <= mid) {
                        cur_dist += next_length;
                    } else {
                        cur_dist = 0;
                        num_workers_used++;  // new worker
                    }
                    cur_idx = next_idx;
                    next_idx = (next_idx + 1) % num_shrines;

                    if (num_workers_used > w) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    hi = mid;
                } else {
                    lo = mid;
                }
            }
            // cout << "hi " << hi << endl;
            lowest_dist = min(lowest_dist, hi);
        }
        cout << fixed << setprecision(1) << lowest_dist + 2000 << endl;
    }

    return 0;
}
