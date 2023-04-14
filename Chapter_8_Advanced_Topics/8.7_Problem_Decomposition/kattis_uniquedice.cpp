/**Kattis - uniquedice
 * Simple but slightly tedious. We do a preprocessing to colour the graph of "all possible" dice
 * according to whether they are equivalent or not. To do this easily, we represent each dice as a
 * hash of its 6 tuple as a 6 digit base 6 number so all possible dice form a bijection to the
 * numbers [0..6^6-1]. Now a good observation to make is that we only to add 2 edges for each node,
 * a 90 degree rotation about 2 different axes since any other rotation will be equivalent to some
 * linear combination of these 2 rotations. We can then do a simple dfs to colour the graph and
 * count how many dice are there of each colour in the input provided.
 * 
 * Time: O(n), Space: O(n)
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

tuple<int, int, int, int, int, int> unhash(int dice)
{
    int r = dice % 6;
    dice /= 6;
    int l = dice % 6;
    dice /= 6;
    int b = dice % 6;
    dice /= 6;
    int f = dice % 6;
    dice /= 6;
    int d = dice % 6;
    dice /= 6;
    int u = dice % 6;
    return {u, d, f, b, l, r};
}
int hasher(int u, int d, int f, int b, int l, int r)
{
    return r + 6 * (l + 6 * (b + 6 * (f + 6 * (d + 6 * u))));
}
int rotate_x(int dice)
{
    auto [u, d, f, b, l, r] = unhash(dice);
    return hasher(f, b, d, u, l, r);
}
int rotate_y(int dice)
{
    auto [u, d, f, b, l, r] = unhash(dice);
    return hasher(u, d, r, l, f, b);
}

vector<int> colour, numincolour;
int cur_col;
void dfs(int dice)
{
    if (colour[dice] != -1) return;
    colour[dice] = cur_col;
    dfs(rotate_x(dice));
    dfs(rotate_y(dice));
}
int main()
{
    fast_cin();
    int sp6 = 6 * 6 * 6 * 6 * 6 * 6;
    colour.assign(sp6, -1);
    cur_col = 0;
    for (int i = 0; i < sp6; i++) {
        if (colour[i] == -1) {
            dfs(i);
            cur_col++;
        }
    }
    numincolour.assign(cur_col, 0);
    int n;
    cin >> n;
    while (n--) {
        int u, d, f, b, l, r;
        cin >> u >> d >> f >> b >> l >> r;
        u--;
        d--;
        f--;
        b--;
        l--;
        r--;
        int dice = hasher(u, d, f, b, l, r);
        numincolour[colour[dice]]++;
    }
    int ans = 0;
    for (int i = 0; i < cur_col; i++) {
        ans = max(ans, numincolour[i]);
    }
    cout << ans << endl;
    return 0;
}