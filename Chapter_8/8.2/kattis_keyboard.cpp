/**Kattis - keyboard
 * This is a slightly tedious state-space BFS question. Our state is (row, col, num of chars
 * pressed) and our transitions are moving in the 4 cardinal directions. 
 * 
 * Note however, that to avoid the problem to needing to press a key multiple times without
 * moving, pre-process the string by compressing adjacent duplicated characters. We also need
 * to take care of the edge case that (0, 0) is the first character of the string.
 * 
 * If we needed to speed things up even more, we could pre-process the keyboard in O(hw max(h, w))
 * time to allow for O(1) rather than O(max(h, w)) time to move in the 4 cardinal directions.
 * However, we could AC without this.
 * 
 * Time: O(hw max(h, w) * n), Space: O(hwn)
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

void removeAdjacentDuplicates(string &s) { // compresses adjacent duplicated characters, into a single instance of that char
    char prev = '~'; // a character that is not in the string
    for (auto it = s.begin(); it != s.end(); it++) {
        if (prev == *it) {
            s.erase(it);
            it--;
        } else {
            prev = *it;
        }
    }
}

int h, w;
int dist[50][50][10009];  // r, c, num chars typed
char keys[50][50];
queue<tuple<int, int, int>> q;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    fast_cin();
    cin >> h >> w;
    memset(dist, -1, sizeof(dist));

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> keys[r][c];
        }
    }

    string target;
    cin >> target;
    target += '*';
    int initial_length = target.length();
    removeAdjacentDuplicates(target);
    int target_length = target.length();

    if (target[0] == keys[0][0]) { // edge case where we start with the correct key
        dist[0][0][1] = 0;
        q.push(make_tuple(0, 0, 1));
    } else {
        dist[0][0][0] = 0;
        q.emplace(0, 0, 0);
    }

    while (!q.empty()) {
        auto &[r, c, num] = q.front();
        // cout << r << " " << c << " " << num << " " << dist[r][c][num] << endl;
        q.pop();
        if (num == target_length) {
            cout << dist[r][c][num] + initial_length << endl;
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r;
            int nc = c;

            bool edge = false;
            while (keys[nr][nc] == keys[r][c]) {
                nr += dr[i];
                nc += dc[i];
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                    edge = true;
                    break;
                }
            }
            if (edge) continue;

            if (keys[nr][nc] == target[num]) {
                if (dist[nr][nc][num + 1] == -1) {
                    dist[nr][nc][num + 1] = dist[r][c][num] + 1;
                    q.emplace(nr, nc, num + 1);
                }
            } else {
                if (dist[nr][nc][num] == -1) {
                    dist[nr][nc][num] = dist[r][c][num] + 1;
                    q.emplace(nr, nc, num);
                }
            }
        }
    }

    return 0;
}