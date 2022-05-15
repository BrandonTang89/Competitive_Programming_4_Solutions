/* Kattis - musical chairs

A variation on the josephus problem

Observation 1:
    since n < 1e4, a O(n^2) brute force approach should be fine. Note that k can
    be very large, to prevent moving around the array an excesssive number of times,
    we should just take k mod the number of people left

Time: O(n^2), Mem: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

int n;
int k[10001];
bool dead[10001];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> k[i];
        k[i]--;
    }

    int num_dead = 0;
    int pos = 0;
    int moves;
    while (num_dead < n - 1) {
        moves = k[pos] % (n - num_dead);
        while (moves > 0) {  // simulate movement, cycling back and skipping dead people
            pos++;
            if (pos == n) pos = 0;
            if (!dead[pos]) moves--;
        }
        // printf ("pos %d has died\n", pos);
        dead[pos] = 1;
        num_dead++;

        while (dead[pos]) {  // move to the next live person
            pos++;
            if (pos == n) pos = 0;
        }
    }

    cout << pos + 1 << endl;

    return 0;
}