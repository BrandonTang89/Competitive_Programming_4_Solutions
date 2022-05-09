/**Kattis - amazing
 * Use a DFS tree to explore the maze. Interactive problem so remember to flush output and test properly.
 * 
 * Time: O(V), Space: O(V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

set<pair<int, int>> visited;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
string dir[] = {"up", "right", "down", "left"};
void dfs(pair<int, int> cur, pair<int, int> prev){
    visited.insert(cur);
    string res;

    int prev_dir = -1;
    for (int i = 0; i < 4; i++){
        pair<int, int> next = make_pair(cur.first + dr[i], cur.second + dc[i]);
        if (visited.count(next) == 0){
            cout << dir[i] << endl << flush;
            cin >> res;

            if (res == "wall")continue;
            if (res == "solved"){
                exit(0);
            }
            if (res == "ok"){
                dfs(next, cur);
            }
            assert(res != "wrong");
        }
        else{
            if (next == prev){
                prev_dir = i;
            }
        }
    }
    if (cur != make_pair(0, 0)){
        cout << dir[prev_dir] << endl << flush;
        cin >> res;
        assert(res == "ok");
    }
    else{
        cout << "no way out" << endl << flush;
        exit(0);
    }

}

int main(){
    dfs(make_pair(0, 0), make_pair(0, 0));

    return 0;
}