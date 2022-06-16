/**Kattis - andrewant
 * If we imagine the line as being infinitely long, eventually we reach a point where we have 2
 * groups of ants: a left walking group on the left on a right walking group. Now observe that
 * since 2 ants never cross, it means that the order of the ants at this stage is the same as the
 * order of ants at the start. As such, the right-most left walking ant is the kth ant at the start,
 * where the ants are ordered from left to right and there are k left walking ants. Similarly, the
 * left-most right walking ant is the k+1th ant at the start. These 2 ants are the only candidates
 * for the longest standing ant.
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int l, n, max_n;
vector<int> ants; // initial positions of the ants
int main() {
    while (cin >> l >> n) {
        int num_moving_left = 0;
        max_n = 0;
        int longest_moving_left = -1, longest_moving_right = -1;
        ants.clear();
        for (int i = 0; i < n; i++) {
            int x;
            char dir;
            cin >> x >> dir;
            ants.emplace_back(x);
            num_moving_left += (dir == 'L');

            if (dir == 'L') {
                if (longest_moving_left == -1) {
                    longest_moving_left = x;
                } else {
                    longest_moving_left = max(longest_moving_left, x);
                }
            } else if (dir == 'R') {
                if (longest_moving_right == -1) {
                    longest_moving_right = l - x;
                } else {
                    longest_moving_right = max(longest_moving_right, l - x);
                }
            }
        }
        sort(ants.begin(), ants.end());
        if (longest_moving_left == longest_moving_right) {
            printf("The last ant will fall down in %d seconds - started at %d and %d.\n",
                   longest_moving_left, ants[num_moving_left - 1], ants[num_moving_left]);
        } else if (longest_moving_left > longest_moving_right) {
            printf("The last ant will fall down in %d seconds - started at %d.\n",
                   longest_moving_left, ants[num_moving_left - 1]);
        } else {
            printf("The last ant will fall down in %d seconds - started at %d.\n",
                   longest_moving_right, ants[num_moving_left]);
        }
    }

    return 0;
}