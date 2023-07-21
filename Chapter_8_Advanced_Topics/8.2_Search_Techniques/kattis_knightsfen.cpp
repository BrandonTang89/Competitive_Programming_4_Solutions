/**Kattis - knightsfen
 * State space BFS. Doing the "recursive backtracking" is suboptimal and my solution was too slow. I
 * should stop believing the question categories, especially when the better solution is clear...
 * 
 * Time: O(1 (tho it is some big contant)), Space: O(1) 
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
int dr[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dc[] = {1, 2, 2, 1, -1, -2, -2, -1};

unordered_map<string, int> dist;
int main()
{
    fast_cin();
    queue<string> q;
    q.push("111110111100 110000100000");
    dist["111110111100 110000100000"] = 0;
    while (!q.empty()) {
        string cur = q.front();
        q.pop();
        int d = dist[cur];
        if (d == 10) continue;

        int br = -1, bc = -1;
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (cur[r * 5 + c] == ' ') {
                    br = r;
                    bc = c;
                }
            }
        }
        assert(br != -1 && bc != -1);
        for (int i = 0; i < 8; i++) {
            int nr = br + dr[i];
            int nc = bc + dc[i];
            if (nr < 0 || nr >= 5 || nc < 0 || nc >= 5) continue;
            string next = cur;
            swap(next[br * 5 + bc], next[nr * 5 + nc]);
            if (dist.find(next) == dist.end()) {
                dist[next] = d + 1;
                q.push(next);
            }
        }
    }

    int tc;
    cin >> tc;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (tc--) {
        string s;
        for (int r = 0; r < 5; r++) {
            string x;
            getline(cin, x);
            s += x;
        }
        if (dist.find(s) == dist.end()) {
            cout << "Unsolvable in less than 11 move(s)." << endl;
        }
        else {
            cout << "Solvable in " << dist[s] << " move(s)." << endl;
        }
    }
    return 0;
}