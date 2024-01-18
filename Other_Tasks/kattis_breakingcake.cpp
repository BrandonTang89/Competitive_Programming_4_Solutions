/**Kattis - breakingcake
 * A 3D version of kattis - cake. Similar to that, we can always do this constructively. Since there
 * are more dimensions this time, we need to code it in a rather uniform manner over each dimension
 * to ensure correctness without too much effort.
 *
 * The idea is to first isolate the pieces that belong to the plane with the lowest x coordinate.
 * We cut this and all the planes with lower x coordinates but don't contain chocolate pieces.
 *
 * For each plane, we get the line that contains chocolates with the lowest y coordinates. We cut
 * that line and all other lines with lower y coordinates but don't contains chocolate pieces.
 *
 * Within this line, we cut away pieces, in the obvious manner.
 *
 * Time: O(m), Space: O(m)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (true) {
        int a, b, c, m;
        cin >> a;
        if (a == -1) break;
        cin >> b >> c >> m;
        vector<tuple<int, int, int, int>> arr(m);
        vector<tuple<int, int, int, int, int, int>> sols(m);  // (x, u), (y, v), (z, w)

        int maxX = 0;
        for (int i = 0; i < m; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            maxX = max(maxX, x);
            arr[i] = make_tuple(x, y, z, i);
        }
        sort(arr.begin(), arr.end());

        int prevX = 0;
        int cur = 0;
        while (cur < m) {
            int curX = get<0>(arr[cur]);

            vector<tuple<int, int, int, int>> thisPlane;
            int maxY = 0;
            while (cur < m && get<0>(arr[cur]) == curX) {
                thisPlane.push_back(arr[cur]);
                maxY = max(maxY, get<1>(arr[cur]));
                cur++;
            }

            int rightX = (curX == maxX ? a : curX);
            // Our cut will cut [PrevX + 1 .. rightX]
            int prevY = 0;
            int cur2 = 0;
            while (cur2 < (int)thisPlane.size()) {
                int curY = get<1>(thisPlane[cur2]);
                vector<tuple<int, int, int, int>> thisLine;
                int maxZ = 0;
                while (cur2 < (int)thisPlane.size() && get<1>(thisPlane[cur2]) == curY) {
                    thisLine.push_back(thisPlane[cur2]);
                    maxZ = max(maxZ, get<2>(thisPlane[cur2]));
                    cur2++;
                }

                int rightY = (curY == maxY ? b : curY);
                // Our cut will cut [PrevY + 1 .. curY]

                int prevZ = 0;
                for (auto [x, y, z, i] : thisLine) {
                    assert(x == curX && y == curY);

                    int rightZ = (z == maxZ ? c : z);
                    // Our cut will cut [PrevZ + 1 .. curZ]

                    sols[i] = {prevX + 1, rightX, prevY + 1, rightY, prevZ + 1, rightZ};
                    prevZ = z;
                }

                prevY = curY;
            }
            prevX = curX;
        }

        cout << "YES" << endl;
        for (auto [x, u, y, v, z, w] : sols) {
            cout << x << " " << y << " " << z << " " << u << " " << v << " " << w << endl;
        }
    }

    return 0;
}