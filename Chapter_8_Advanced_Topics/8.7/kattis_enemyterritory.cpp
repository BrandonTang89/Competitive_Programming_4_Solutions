/**Kattis - enemyterritory
 * Pretty cool question actually!! We can do some interesting visualisation: First we do a
 * multi-source BFS from all the enemy bases, creating a 3D graph of min dist from an enemy
 * base. From here, we try walking from source to dest with a minimum walkable elevation.
 * BSTA for this minimum walkable elevation. The "try walking" check should be done with
 * BFS to get the shortest distance at each walkable elevation.
 * 
 * Time: O(hw log hw), Space: O(hw)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, h, w;
int s_r, s_c, dest_r, dest_c;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
int dist[1001][1001];
queue<pair<int, int>> q;

int can_travel(int min_enemy){
    while (!q.empty()) q.pop();
    vector<vector<int>> dist2(h, vector<int>(w, -1));

    q.push({s_r, s_c});
    dist2[s_r][s_c] = 0;
    if (dist[s_r][s_c] < min_enemy) return -1; // important check

    while (!q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for (int i=0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
            if (dist[nr][nc] < min_enemy)continue;
            if (dist2[nr][nc] == -1){
                dist2[nr][nc] = dist2[r][c] + 1;
                q.push(make_pair(nr, nc));
            }
        }
    }
    return dist2[dest_r][dest_c];
}
int main(){
    cin >> n >> h >> w;
    cin >> s_r >> s_c >> dest_r >> dest_c;
    memset(dist, -1, sizeof(dist));
    for (int i=0; i < n; i++){
        int r, c;
        cin >> r >> c;
        dist[r][c] = 0;
        q.push(make_pair(r, c));
    }

    // Multisource BFS
    while (!q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for (int i=0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
            if (dist[nr][nc] == -1){
                dist[nr][nc] = dist[r][c] + 1;
                q.push(make_pair(nr, nc));
            }
        }
    }

    // BSTA for Minimum Closest Distance
    int lo = 0, hi = h+w+2;
    while (lo + 1 < hi){
        int mid = (lo + hi) / 2;
        if (can_travel(mid) != -1) lo = mid; // we can try going further away
        else hi = mid - 1; // we need to be closer
    }
    if (lo < hi){
        if (can_travel(hi) != -1)lo = hi;
    }
    cout << lo << " " << can_travel(lo) << endl;

    return 0;
}