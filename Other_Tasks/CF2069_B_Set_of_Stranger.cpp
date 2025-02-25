/**CF2069B
 * For each colour, find out ifs doable in 1 or 2 moves (always doable in 2 moves via checkerboard style approach)
 */
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int main() {
    fast_cin();
    int t;
    cin >> t;
    while (t--) {
        int h, w;
        cin >> h >> w;
        vector<vector<int>> arr(h, vector<int>(w));
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                cin >> arr[i][j];
            }
        }

        unordered_map<int, bool> d;

        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                int colour = arr[r][c];
                if (d[colour]) {
                    continue;
                }

                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nr >= 0 && nr < h && nc >= 0 && nc < w) {
                        if (arr[nr][nc] == colour) {
                            d[colour] = true;
                            break;
                        }
                    }
                }
            }
        }

        vector<int> costs;
        for (const auto& pair : d) {
            costs.push_back(pair.second ? 2 : 1);
        }

        int total_cost = accumulate(costs.begin(), costs.end(), 0);
        int max_cost = *max_element(costs.begin(), costs.end());
        cout << total_cost - max_cost << endl;
    }

    return 0;
}