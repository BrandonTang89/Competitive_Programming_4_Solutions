/**Kattis - jugglingpatterns
 * Very confusing problem statement. We need to prune useless information like the stuff about
 * hands. Essentially we should go beat by beat and check if 2 balls are falling at the same time or
 * not. We should also check that if we don't throw a ball, we don't catch a ball at the beat since
 * "If a ball is caught on a beat, it should be thrown on the same beat."
 * 
 * Note that an issue is regarding how many cycles to run the checks for. I just guessed that 100*n
 * should be enough... I have no proof for it tho.
 * 
 * Time: O(100 n log 9), Space: O(9)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, greater<int>> pq;
string p;
int main() {
    while (cin >> p) {
        while (!pq.empty()) pq.pop();
        int n = p.size();
        int total = 0;
        for (int i = 0; i < n; i++) {
            total += p[i] - '0';
        }
        if (total % n != 0) {
            cout << p << ": invalid # of balls" << endl;
            continue;
        }

        int num_balls = total / n;
        bool valid = true;

        for (int i = 0; i < 100 * n; i++) {
            int counter = 0;
            if (p[i % n] != '0') {
                while (pq.size() > 0 && pq.top() == i) {
                    pq.pop();
                    counter++;
                }
                if (counter > 1) {
                    valid = false;
                    break;
                }
                pq.push(i + p[i % n] - '0');
            } else {
                if (pq.size() > 0 && pq.top() == i) { // check if we catch a ball on the beat
                    valid = false;
                    break;
                }
            }
        }

        if (valid) {
            cout << p << ": valid with " << num_balls << " balls" << endl;
        } else {
            cout << p << ": invalid pattern" << endl;
        }
    }

    return 0;
}