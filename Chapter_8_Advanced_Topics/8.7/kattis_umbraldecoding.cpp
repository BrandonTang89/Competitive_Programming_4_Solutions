/**Kattis - umbraldecoding
 * A question that is simple in theory, but hard in practise. The hint given is recursive subdivision. Ie, we
 * for a given umbra and rectangle, we try to cut away all the umbra parts of the rectangle. If the rectangle
 * is completely in the umbra, we ignore it. If its completely out of the umbra, we add it to our output. Else,
 * we cut the rectangle into 4 almost equally sized parts and repeat. The key challenge is determining if the
 * rectangle is completely in the umbra or completely out of the umbra. The first can be achieved by observing
 * that if all 4 corners of the rectangle are in the umbra, then the rectangle is in the umbra. The second can be
 * done by first determining the point on the rectangle with the lowest value of abs(x-p)^3 + abs(y-q)^3. I first
 * used some super complex times of ternary search to achieve this, but it didn't work with large numbers well.
 * I then realised that we can just check if the center of the umbra is in the rectangle, if so then we definitely
 * are not out of the umbra. else the lowest point will be the point on the rectangle's border which is closest
 * to the center of the umbra. Then we just check if this point is inside the umbra.
 * 
 * To check if a point is inside the umbra, note that we should check if the point is super far away and if so,
 * don't continue checking (since the check will overflow and its obviously impossible for the point to be in the
 * umbra). 
 * 
 * Time: O(?), Space: O(?)
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

ll val(tuple<int, int, int> safe_pt, int x, int y) {
    auto [p, q, b] = safe_pt;
    return (ll)abs(x - p) * (ll)abs(x - p) * (ll)abs(x - p) +
           (ll)abs(y - q) * (ll)abs(y - q) * (ll)abs(y - q);
}
bool inside(tuple<int, int, int> safe_pt, int x, int y) {
    return (val(safe_pt, x, y) <= (ll)get<2>(safe_pt));
}

bool point_in_rect(tuple<int, int, int> pt, tuple<int, int, int, int> rect) {
    auto [x, y, b] = pt;
    auto [x1, y1, x2, y2] = rect;
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

pair<int, int> get_lowest_point2(tuple<int, int, int> safe_pt, tuple<int, int, int, int> rect) {
    auto [x0, y0, x1, y1] = rect;
    auto [p, q, b] = safe_pt;

    int x, y;
    if (x0 <= p && p <= x1) {
        x = p;
    } else if (x0 > p) {
        x = x0;
    } else {
        x = x1;
    }

    if (y0 <= q && q <= y1) {
        y = q;
    } else if (y0 > q) {
        y = y0;
    } else {
        y = y1;
    }

    return {x, y};
}
void process_rect(vector<tuple<int, int, int, int>> &dest_rects, tuple<int, int, int, int> rect,
                  int p, int q, int b) {
    auto [x0, y0, x1, y1] = rect;
    // cout << "dealing with : " << x0 << " " << y0 << " " << x1 << " " << y1 << endl;
    // if the entire rect is inside the umbra, just ignore
    vector<pair<int, int>> corners = {{x0, y0}, {x0, y1}, {x1, y0}, {x1, y1}};
    bool all_inside = true;
    for (auto [x, y] : corners) {
        if (abs(x - p) + abs(y - q) > 1000 || !inside(make_tuple(p, q, b), x, y)) {
            all_inside = false;
            break;
        }
    }
    if (all_inside) {
        return;
    }

    // if the rect is completely outside the umbra, just add it
    if (!point_in_rect(make_tuple(p, q, b), rect)) {
        // check for obviously outside the umbra
        auto lowest = get_lowest_point2(make_tuple(p, q, b), rect);
        if (abs(lowest.first - p) + abs(lowest.second - q) > 1000 ||
            !inside(make_tuple(p, q, b), lowest.first, lowest.second)) {
            dest_rects.push_back(rect);
            return;
        }
    }

    // if the rect is partially inside the umbra, split it
    // cout << "splitting" << endl;
    int half_x = (x0 + x1) / 2, half_y = (y0 + y1) / 2;
    process_rect(dest_rects, make_tuple(x0, y0, half_x, half_y), p, q, b);
    if (half_x + 1 <= x1) {
        process_rect(dest_rects, make_tuple(half_x + 1, y0, x1, half_y), p, q, b);
    }
    if (half_y + 1 <= y1) {
        process_rect(dest_rects, make_tuple(x0, half_y + 1, half_x, y1), p, q, b);
    }
    if (half_x + 1 <= x1 && half_y + 1 <= y1) {
        process_rect(dest_rects, make_tuple(half_x + 1, half_y + 1, x1, y1), p, q, b);
    }
}
vector<tuple<int, int, int, int>> rects1, rects2;
int n, k;
int main() {
    cin >> n >> k;
    int p, q, b;
    rects1.push_back({0, 0, n, n});
    for (int i = 0; i < k; i++) {
        auto &source_rects = (i % 2 == 0) ? rects1 : rects2;
        auto &dest_rects = (i % 2 == 0) ? rects2 : rects1;

        cin >> p >> q >> b;

        dest_rects.clear();
        for (auto rect : source_rects) {
            process_rect(dest_rects, rect, p, q, b);
        }
    }

    auto &final_rects = (k % 2 == 0) ? rects1 : rects2;
    ll ans = 0;
    for (auto &rect : final_rects) {
        auto &[x0, y0, x1, y1] = rect;
        ans += ((ll)x1 - x0 + 1) * ((ll)y1 - y0 + 1);
    }
    cout << ans << endl;
    return 0;
}
