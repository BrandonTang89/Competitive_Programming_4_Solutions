/* Kattis - sellingspatulas
This problem is simple in theory, but I found alot of problem when trying to use integers to
represent the profits. Im not sure what the problem was but I decided to change to doubles and then
it worked?

Anyway, the solution is just kadane without much changes. Except to select the answer not just
based on value but also based on duration and start time.

Time: O(1440), Space: O(1440)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9
#define double_equal(a, b) (abs(a - b) <= EPS)

int n, t;
double cur;
vector<double> ori;
int main() {
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;
        ori.assign(1440, -0.08);
        for (int i = 0; i < n; i++) {
            scanf("%d %le", &t, &cur);
            ori[t] += cur;
        }

        // Kadane's Algorithm on Ori
        double sum = 0, ans = 0;
        int sum_start = 0, sum_duration = 0, ans_start = 0, ans_duration = 0;
        for (int i = 0; i < 1440; i++) {
            sum += ori[i];
            // cout << sum <<endl;
            if (sum < EPS) { // better to reset sum
                sum = 0;
                sum_start = i + 1;
                sum_duration = 0;
            } else { // extend sum to current value
                sum_duration++;
            }

            // Check if current sum is a better answer
            if (sum - ans > EPS) {
                // if strictly less than
                ans = sum;
                ans_start = sum_start;
                ans_duration = sum_duration;
            } else if (double_equal(ans, sum)) {
                // check if our time_period is shorter or not if equal
                if (sum_duration < ans_duration) {
                    // sum period is shorter
                    ans_start = sum_start;
                    ans_duration = sum_duration;
                }
            }
            // else we take the earlier one, ie no change
        }

        if (double_equal(0, ans)) {
            cout << "no profit" << endl;
        } else {
            printf("%.2f %d %d\n", ans, ans_start, ans_start + ans_duration - 1);
        }
    }

    return 0;
}