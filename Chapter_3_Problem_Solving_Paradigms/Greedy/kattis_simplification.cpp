/**Kattis - simplification
 * Greedy problem, with the greedy being written in the question: remove the smallest area. We
 * maintain a priority queue of areas and their center point indices and always remove the point
 * with the smallest area. Then we update up to 2 other triangles, deleting the adjacent triangles
 * and updating them with their new left / right point that skips over the removed point. This task
 * tests your proficiency to work with iterators meticulously since we store the points and the
 * areas in sets of pairs and tuples respectively. C++17 structured bindings make the code much more
 * readable.
 * 
 * Time: O(n log n), Space: O(n)
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

int n, m;
set<tuple<int, int, int>> pts;  // index, x, y
set<pair<double, int>> areas;   // area, index of center pt

double get_area(int x1, int y1, int x2, int y2, int x3, int y3) {  // shoelace area
    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

int main() {
    fast_cin();
    cin >> n >> m;
    for (int i = 0; i < n + 1; i++) {
        int x, y;
        cin >> x >> y;
        pts.emplace(i, x, y);  // initially all points are in the set
    }

    auto left = pts.begin(), right = pts.begin(), mid = pts.begin();
    right++;
    right++;
    mid++;
    for (int i = 1; i < n; i++) {
        auto [i1, x1, y1] = *left;
        auto [i2, x2, y2] = *mid;
        auto [i3, x3, y3] = *right;
        double area = get_area(x1, y1, x2, y2, x3, y3);
        assert(i == i2);
        areas.emplace(area, i);

        left++;
        mid++;
        right++;
    }

    for (int i = 0; i < n - m; i++) {
        auto [smallest_area, imid] = *areas.begin();
        areas.erase({smallest_area, imid});
        auto mid = pts.lower_bound({imid, -9000, -9000});
        auto left = mid;
        left--;
        auto right = mid;
        right++;

        auto [i2, x2, y2] = *mid;
        auto [i1, x1, y1] = *left;
        auto [i3, x3, y3] = *right;

        assert(i2 == imid);

        cout << i2 << endl;

        if (left != pts.begin()) {
            auto leftleft = left;
            leftleft--;
            auto [i4, x4, y4] = *leftleft;
            double area = get_area(x1, y1, x2, y2, x4, y4);
            areas.erase({area, i1});  // remove the one centered on left
            areas.emplace(get_area(x4, y4, x1, y1, x3, y3), i1);
        }
        if (right != (--pts.end())) {
            auto rightright = right;
            rightright++;
            auto [i4, x4, y4] = *rightright;
            double area = get_area(x3, y3, x2, y2, x4, y4);
            areas.erase({area, i3});  // remove the one centered on right
            areas.emplace(get_area(x1, y1, x3, y3, x4, y4), i3);
        }
        pts.erase(mid);
        areas.erase({smallest_area, imid});
    }

    return 0;
}