/**Kattis - safe
 * We use BFS in a state space search. The state is the lock combination, we read the numbers
 * as a base 4 number. Again, we need to manually calculate the transition masks. And we need
 * to write a custom function to apply a transition. For each digit in the base 4 representation
 * of the numbers, we add cur and mask, then modulo 4.
 * 
 * Time: O(4^n), Space: O(4^n)
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

int transition_masks[] = {87056, 86276, 86081, 66896, 17732, 5441, 66581, 16661, 4181};

int apply_mask(int cur, int mask){
    int res = 0;
    int multiplier = 1;
    while (cur > 0 || mask > 0){
        int x = ((mask % 4) + (cur % 4)) % 4;
        res += x * multiplier;
        mask /= 4;
        cur /= 4;
        multiplier *= 4;
    }
    return res;
}

int temp;
map<int, int> dist;
queue<int> q;
int main() {
    int source = 0;
    for (int i=0; i<9; i++){
        cin >> temp;
        source *= 4;
        source += temp;
    }

    dist[source] = 0;
    q.push(source);
    while (!q.empty()){
        int cur = q.front();
        q.pop();

        if (cur == 0){
            cout << dist[cur] << endl;
            return 0;
        }
        for (int i=0; i<9; i++){
            int new_mask = apply_mask(cur, transition_masks[i]);

            if (dist.count(new_mask) == 0){
                dist[new_mask] = dist[cur] + 1;
                q.push(new_mask);
            }
        }
    }

    cout << -1 << endl;

    return 0;
}