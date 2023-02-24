/**Kattis - gruesomecave
 * The difficulty is in the preprocessing of the graph to get the probability that the grue is in
 * each cell. For each empty cell, we have the constraint that P(cell) = sum(P(neighbour) /
 * num_neighbours(neighbour)). As well as the constraint that the sum of all P(cell) = 1. The
 * "correct" way to do this is to set up a system of linear equations and use gaussian elimination
 * to solve it. But fortunately we manage to get away with a simple simulation lol. We start with
 * all cells having the same probability. For each iteration, we distribute the probability of each
 * cell evenly into the neighbours of the cell. We do the simulation for 30k iterations to get it to
 * settle into some stable state. Then we do another 20k iterations to get the average probability
 * of each cell. (Just tried arbitary values of number of iterations until AC. Note that the idea of
 * waiting until it settles in before taking the average is indeed quite an important one).
 *
 * Then we do dijkstra to find the shortest path.
 *
 * Time: O(50k * (h * w) + HW log (HW)), Mem: O(h * w)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> grid;
vector<vector<double>> probabilities[2], ave, dist;
vector<vector<int>> num_neighbours;  // also number of neighbors
priority_queue<tuple<double, int, int>, vector<tuple<double, int, int>>,
               greater<tuple<double, int, int>>>
    pq;
int h, w, num_empty;
int sr, sc, er, ec;
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};
int main()
{
    cin >> h >> w;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    grid.assign(h, vector<char>(w, ' '));
    num_neighbours.assign(h, vector<int>(w, 0));
    for (int i = 0; i < h; i++) {
        string s;
        getline(cin, s);
        for (int j = 0; j < w; j++) {
            grid[i][j] = s[j];
            num_empty += (grid[i][j] == ' ');
            if (grid[i][j] == 'E') {
                sr = i;
                sc = j;
            }
            if (grid[i][j] == 'D') {
                er = i;
                ec = j;
            }
        }
    }
    probabilities[0].assign(h, vector<double>(w, 0));
    probabilities[1].assign(h, vector<double>(w, 0));
    ave.assign(h, vector<double>(w, 0));
    dist.assign(h, vector<double>(w, 1e9));

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (grid[r][c] == ' ') {
                probabilities[0][r][c] = 1.0 / num_empty;

                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] == ' ') {
                        num_neighbours[r][c]++;
                    }
                }
            }
        }
    }

    int num_itr = 50000;
    for (int itr = 0; itr < num_itr; itr++) {
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                if (itr >= 30000) ave[r][c] += probabilities[itr % 2][r][c];
                probabilities[(itr + 1) % 2][r][c] = 0;
            }
        }
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                if (grid[r][c] == ' ') {
                    for (int i = 0; i < 4; i++) {
                        int nr = r + dr[i];
                        int nc = c + dc[i];
                        if (nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] == ' ') {
                            probabilities[(itr + 1) % 2][nr][nc] +=
                                (probabilities[itr % 2][r][c] / ((double)num_neighbours[r][c]));
                        }
                    }
                }
            }
        }
    }

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            ave[r][c] /= 20000;
        }
    }

    dist[sr][sc] = 0;
    pq.push({0, sr, sc});

    while (!pq.empty()) {
        auto [d, r, c] = pq.top();
        pq.pop();
        if (r == er && c == ec) {
            cout << fixed << setprecision(10) << d << endl;
            return 0;
        }
        if (d > dist[r][c]) continue;
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] != '#') {
                if (dist[nr][nc] > dist[r][c] + ave[nr][nc]) {
                    dist[nr][nc] = dist[r][c] + ave[nr][nc];
                    pq.push({dist[nr][nc], nr, nc});
                }
            }
        }
    }

    return 0;
}