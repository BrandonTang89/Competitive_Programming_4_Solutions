/* Kattis - hidingplaces
This is probably the most basic of knightmove questions, if not for the fact that we have to do
conversion from the file and rank indexing to regular 0 indexing, do the BFS, then convert back, then
custom sort.

Also, apparently kattis allows for extra trailing spaces in the output, thats good to know!

Time: O(n), Mem: O(1)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int s_r, s_c, num_tc;
int dr[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dc[] = {1, 2, 2, 1, -1, -2, -2, -1};
string line;
vector<vector<int>> dist;
queue<tuple<int,int>> q;
vector<string> hiding_places;

bool custom_sort(string a, string b){
    if (a[1] > b[1])return true;
    if (a[1] < b[1])return false;

    return (a[0] < b[0]);
}

int main(){
    cin >> num_tc; 
    for (int tc=0;tc<num_tc; tc++){
        cin >> line;
        s_c = line[0] - 'a';
        s_r = line[1] - '1';

        //printf("s_r: %d, s_c: %d\n", s_r, s_c);

        dist.assign(8, vector<int>(8, -1));
        hiding_places.clear();

        dist[s_r][s_c] = 0;
        q.emplace(s_r, s_c);

        
        int max_dist = 0;
        while (!q.empty()){
            auto &[r, c] = q.front();
            q.pop();

            max_dist = max(max_dist, dist[r][c]);
            
            for (int i=0;i<8;i++){
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nc < 0 || nr < 0 || nc >= 8 || nr >= 8)continue;
                if (dist[nr][nc] != -1)continue;

                dist[nr][nc] = dist[r][c] + 1;
                q.emplace(nr, nc);
            }
        }

        for (int r=0;r<8;r++){
            for (int c=0; c<8;c++){
                if (dist[r][c] == max_dist){
                    char file = c + 'a';
                    char rank = r + '1';
                    string s;
                    s.push_back(file);
                    s.push_back(rank);
                    hiding_places.push_back(s);
                }
            }
        }

        sort(hiding_places.begin(), hiding_places.end(), custom_sort);

        cout << max_dist << " ";
        for (auto s: hiding_places){
            cout << s << " ";
        }cout << endl;
        
    }
    return 0;
}