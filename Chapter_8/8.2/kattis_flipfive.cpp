/**Kattis - flipfive
 * Another simple state space search problem. Its abit tedious to manually calculate the
 * masks for clicking each tile tho. Also, edge case where the source == dest. 
 * 
 * Time: O(<< 2^9), Space: O(2^9)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int num_tc;
char square;
queue<int> q;
int dist[513];

int transition_masks[] = {
    11, 23, 38, 89, 186, 308, 200, 464, 416
};

int main(){
    fast_cin();
    cin >> num_tc;
    for (int tc=0; tc<num_tc; tc++){
        int target_mask = 0;
        for (int i=0; i<9; i++){
            cin >> square;
            if (square == '*') target_mask |= (1 << i);
        }

        if (target_mask == 0){
            cout << 0 << endl;
            continue;
        }

        // cout << target_mask << endl;

        memset(dist, -1, sizeof(dist));
        while (!q.empty()) q.pop();
        dist[0] = 0;
        q.push(0);
        bool done = false;
        // we BFS from 0 to target_mask

        while (!q.empty()){
            int cur_mask = q.front();
            q.pop();

            for (int i=0; i<9; i++){
                int new_mask = cur_mask ^ transition_masks[i];
                if (new_mask == target_mask){
                    cout << dist[cur_mask] + 1 << endl;
                    done = true;
                    break;
                }
                if (dist[new_mask] == -1){
                    dist[new_mask] = dist[cur_mask] + 1;
                    q.push(new_mask);
                }
            } 
            if (done) break;
        }
    }

    return 0;
}