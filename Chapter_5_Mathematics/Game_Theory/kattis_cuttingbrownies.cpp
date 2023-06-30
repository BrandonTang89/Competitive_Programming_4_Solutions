/**Kattis - cuttingbrownies
 * The optimal move for Harry is to cut the thinest piece at the middle (as middle as possible).
 * Similarly, the optimal move is for Vicky to cut the shortest piece at the middle.
 * We use a multiset to stare the remaining pieces. We use 2 multisets that allow us to get the
 * shortest and the thinnest pieces in O(log n) time. Since we cannot split a piece of length 1
 * horizontally or a piece of height 1 vertically, we encode this as buffer values hbuf and vbuf.
 * I.e. hbuf is how many extra cuts that Harry can do without changing the pieces in the multisets,
 * and vbuf is the same for Vicky. With this state representation, we need to note the edge cases
 * when the input is of length or width 1.
 * 
 * Time: O(hw log (hw)), Space: O(hw)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, h, w;
multiset<pair<int, int>> hor, ver;
// hor: (x, y) allows us to find the thinest possible to cut horizontally
// ver: (y, x) allows us to find the shortest possible to cut vertically
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> w >> h;
        hor.clear();
        ver.clear();

        hor.insert({w, h});
        ver.insert({h, w});
        int hbuf = 0, vbuf = 0;

        string starter;
        cin >> starter;
        int horPlayer = starter == "Harry" ? 1 : 0;
        int winningPlayer = 0;
        int startPlayer = horPlayer;

        if (w == 1 && h == 1) {
            cout << starter << " cannot win\n";
            continue;
        }
        else if (w == 1) {
            // so we can only cut horizontally
            winningPlayer = 1;
        }
        else if (h == 1) {
            // so we can only cut vertically
            winningPlayer = 0;
        }
        else {
            while (!hor.empty()) {
                assert(hor.size() == ver.size());
                if (horPlayer) {
                    if (hbuf) {
                        hbuf--;
                        horPlayer = 1 - horPlayer;
                        continue;
                    }
                    // cur horizontally
                    auto [x, y] = *hor.begin();
                    hor.erase(hor.begin());
                    ver.erase(ver.find({y, x}));

                    // cut as in the middle as possible
                    assert(y >= 2);
                    int mid = y / 2;
                    if (mid == 1) {
                        vbuf += x - 1;
                    }
                    else {
                        hor.insert({x, mid});
                        ver.insert({mid, x});
                    }
                    if (y - mid == 1) {
                        vbuf += x - 1;
                    }
                    else {
                        hor.insert({x, y - mid});
                        ver.insert({y - mid, x});
                    }
                }
                else {
                    if (vbuf) {
                        vbuf--;
                        horPlayer = 1 - horPlayer;
                        continue;
                    }
                    // cur vertically
                    auto [y, x] = *ver.begin();
                    hor.erase(hor.find({x, y}));
                    ver.erase(ver.begin());

                    // cut as in the middle as possible
                    assert(x >= 2);
                    int mid = x / 2;
                    if (mid == 1) {
                        hbuf += y - 1;
                    }
                    else {
                        hor.insert({mid, y});
                        ver.insert({y, mid});
                    }
                    if (x - mid == 1) {
                        hbuf += y - 1;
                    }
                    else {
                        hor.insert({x - mid, y});
                        ver.insert({y, x - mid});
                    }
                }
                horPlayer = 1 - horPlayer;
            }

            winningPlayer = 1 - horPlayer;  // the one who doesn't need to move
        }

        assert(min(hbuf, vbuf) == 0); // only 1 can be positive
        if (hbuf > 0) {
            winningPlayer = 1;
        }
        else if (vbuf > 0) {
            winningPlayer = 0;
        }
        if (winningPlayer != startPlayer)
            cout << starter << " cannot win\n";
        else
            cout << starter << " can win\n";
    }

    return 0;
}