/**Kattis - robotturtles
 * This is a relatively tedious state-space BFS question. Our state is (row, col, dir, bitmask)
 * where bitmask is represents if we have melted some of the ice castles. Our transitions are
 * turning left, right, moving forward, and melting an ice castle in front of us. We also need
 * to print the solution, so we maintain a parent array to backtrack, keeping in mind the last
 * transition and the previous state, for each state we visit.
 * 
 * Time: O(1), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

map<pair<int, int>, int> castles;
char grid[8][8];
queue<tuple<int, int, int, int>> q;  // r, c, dir, bit mask
map<tuple<int, int, int, int>, int> dist;
map<tuple<int, int, int, int>, pair<char, tuple<int, int, int, int>>> parent;
// direction: [0: up, 1: left, 2: down, 3: right]
// change directions
int turn_left(int dir) { return (dir + 1) % 4; }
int turn_right(int dir) { return (dir + 3) % 4; } // note we cant use -1 since (-1)%4 == -1

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, -1, 0, 1};

vector<char> moves;
void get_sol(int r, int c, int dir, int bm){
    char move = parent[make_tuple(r, c, dir, bm)].first;
    if (move == '~') {
        return;
    }

    moves.push_back(move);
    auto &[nr, nc, ndir, nbm] = parent[make_tuple(r, c, dir, bm)].second;
    get_sol(nr, nc, ndir, nbm);
    return;
}

int main() {
    int castle_count = 0;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            cin >> grid[r][c];
            if (grid[r][c] == 'I') {
                castles[make_pair(r, c)] = castle_count;
                castle_count++;
            }
        }
    }
    parent[make_tuple(7, 0, 3, 0)] = make_pair('~', make_tuple(7, 0, 3, 0));
    dist[make_tuple(7, 0, 3, 0)] = 0;  // bottom left, facing right
    q.push(make_tuple(7, 0, 3, 0));
    while (!q.empty()) {
        auto &[r, c, dir, bm] = q.front();
        q.pop();

        if (grid[r][c] == 'D') {
            get_sol(r, c, dir, bm);  // print solution
            reverse(moves.begin(), moves.end());
            for (auto move : moves) {
                cout << move;
            }
            cout << endl;
            // cout << "length " << dist[make_tuple(r, c, dir, bm)] << endl;
            // cout << "bm: " << bm << endl;
            return 0;
        }

        // Try turning left and right
        int new_dirs[] = {turn_left(dir), turn_right(dir)};
        char moves[] = {'L', 'R', 'F', 'X'};
        for (int i = 0; i < 2; i++) {
            int new_dir = new_dirs[i];
            char move = moves[i];
            if (dist.find(make_tuple(r, c, new_dir, bm)) == dist.end()) {
                dist[make_tuple(r, c, new_dir, bm)] = dist[make_tuple(r, c, dir, bm)] + 1;
                parent[make_tuple(r, c, new_dir, bm)] = make_pair(move, make_tuple(r, c, dir, bm));
                q.push(make_tuple(r, c, new_dir, bm));
            }
        }

        // get front square
        int nr = r + dr[dir];
        int nc = c + dc[dir];

        if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8 || grid[nr][nc] == 'C') {
            continue;
        }

        // ice castle
        if (grid[nr][nc] == 'I') {
            if (!(bm & (1 << castles[make_pair(nr, nc)]))) {  // ice castle not blown up

                int new_bm = bm | (1 << castles[make_pair(nr, nc)]);
                if (dist.find(make_tuple(r, c, dir, new_bm)) == dist.end()) {
                    dist[make_tuple(r, c, dir, new_bm)] = dist[make_tuple(r, c, dir, bm)] + 1;
                    parent[make_tuple(r, c, dir, new_bm)] =
                        make_pair('X', make_tuple(r, c, dir, bm));
                    q.push(make_tuple(r, c, dir, new_bm));
                }
                continue;
            }
        }

        // if front square is empty or diamond or blown up ice castle
        if (dist.find(make_tuple(nr, nc, dir, bm)) == dist.end()) {
            dist[make_tuple(nr, nc, dir, bm)] = dist[make_tuple(r, c, dir, bm)] + 1;
            parent[make_tuple(nr, nc, dir, bm)] = make_pair('F', make_tuple(r, c, dir, bm));
            q.push(make_tuple(nr, nc, dir, bm));
        }
    }

    cout << "no solution" << endl;

    return 0;
}