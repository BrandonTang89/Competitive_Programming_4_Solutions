/* kattis - fire2
This a non-standard floodfill / BFS question.

Observation 1:
    We can model the situation as a simulation where fire and the "person's possible
    position" are both spreading. Fire can spread into the person's position but not the
    other way around. Both fire and person's position cannot spread onto walls.

    Since the person can always jump away from a cell catching on fire but cannot jump
    onto a cell that is about to catch fire, we should always simulate the fire first.
    This means that at clock cycle, we propate each propagatable fire cell first before
    doing the same for the person cells.

    This can be implemented with the use of a deque to store the upcoming propagatable
    cells. The same BFS frontier idea is kept, updating this deque with new frontier cells.
    Fire cells are put at the front of the deque while person cells are put at the back.

    However, we notice that one deque will not be a good idea because we don't know what
    calls are from what time. This could be solved by adding a 4th parameter of "clock"
    time but we choose instead to use 2 separate deques. We clear all the propagatable
    cells from the primary deque and put their children into the secondary deque. When the
    primary deque is empty, we increment the clock and swap the secondary and primary deque.

Amortized Analysis:
    Even though there could be up to O(hw) cells in the propagation queue at any time,
    we note that after a person cell propagates once, that cell will only need to propagate again
    if it is covered by fire. This means that at most, each cell propagates twice, once when the person
    spreads onto the cell, and a second time when the fire spreads onto the tile. This means at most 
    each cell is processed twice in the entire algorithm.

Time: O(hw), Mem: O(hw)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int ttc, w, h;
vector<vector<char>> grid;
deque<tuple<int, int, int>> q1, q2; // type (0 for fire, 1 for person), r, c
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

int main(){
    fast_cin();
    cin >> ttc;
    for (int tc=0;tc<ttc;tc++){
        cin >> w >> h;
        grid.assign(h, vector<char>(w, '.'));
        q1.clear();
        q2.clear();
        for (int r=0;r<h; r++){
            for (int c=0;c<w;c++){
                cin >> grid[r][c];
                
                if (grid[r][c] == '@'){
                    q1.emplace_back(1, r, c);
                }
                else if (grid[r][c] == '*'){
                    q1.emplace_back(0, r, c);
                }
            }
        }

        int clock = 1;
        bool escaped = false;
        while (!(q1.empty() && q2.empty())){ // while not both empty
            auto &pq = ((clock&1) ? q1 : q2); // odd clock -> (pq == q1, sq == q2)
            auto &sq = ((clock&1) ? q2 : q1); 

            while(!pq.empty()){ // while primary queue not empty
                auto [type, r, c] = pq.front();
                //printf("type: %d, r: %d, c: %d\n", type, r, c);
                pq.pop_front();

                for (int i=0;i<4;i++){
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nc < 0 || nr < 0 || nc >= w || nr >= h){
                        if (type == 1){
                            escaped = true;
                            break;
                        }
                        continue;
                    }

                    if (grid[nr][nc] == '#' || grid[nr][nc] == '*')continue;
                    if (type == 1 && grid[nr][nc] == '@') continue; // person has no reason to go backwards

                    grid[nr][nc] = ((type == 1) ? '@' : '*');

                    if (type == 1)
                        sq.emplace_back(type, nr, nc);
                    else
                        sq.emplace_front(type, nr, nc);
                }
                if(escaped)break;
            }

            if(escaped)break;
            clock++;
        }

        if (escaped){
            cout << clock << endl;
        }
        else{
            cout << "IMPOSSIBLE" << endl;
        }
    }
    return 0;
}