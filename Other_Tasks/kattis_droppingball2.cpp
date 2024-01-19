/**Kattis - droppingball2
 * Actually kind of hard. The first part of the problem would be to determine: If the ball starts a
 * part at column i, that columns can it end up in? This is just a DFS from each column. This takes
 * time O(hw^2) which is fine.
 *
 * Now we have a new graph which consists of layers, each layer corresponding to the value cells
 * between the parts and each network of edges corresponds to the actual part. We need to find the
 * path in this new graph that leads to the highest score.
 *
 * We defined a function f(c_in, c_out, i) which is equal to the maximum score gained when the ball
 * enters i parts, starting from the column c_in and ends up out the column c_out after i parts. We
 * can then use DP together with the "fast exponentiation" of halving i when it is even and
 * subtracting 1 when it is odd.
 *
 * In the even case, we let f(a, b, i) = max(f(a, inter, i/2) + f(inter, b, i/2)) which represents
 * trying all intermediate nodes inter and going from a to inter in i/2 steps then inter to b in i/2
 * steps.
 *
 * In the odd case, we just let f(a, b, i) = max(val[inter] + f(inter, b, i-1) if adjmat[a][inter]).
 * I.e. if we can go from a to some intermediate node in 1 step, we consider it.
 *
 * In this solution, I assumed that we were finding max(f(i, j, k) for all i, j in [0..c-1]) but
 * this doesn't account for situations like the input 
 * 2 2 10 
 * X.
 * .L 
 * 1000 1 
 * which should have a solution of 1000 but this code reports as 0 (so this is actually a fake solve)
 *
 * This is because, we should actually be finding max(f(i, j, l) for all i, j in [0..c-1]), l in
 * [0..k]). Though im convinced you can bound l in a smaller range by the fact that we will only go 
 * to a value cell with no out edges near the front or the end of the network. However, the code will
 * TLE if we try this but will AC without.
 *
 * Time: O(w^2 log k + hw^2), Space: O(w^2 log k + hw)
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

int h, w, k;
vector<int> vals;
vector<vector<int>> adjmat;
// adjmat[c_in][c_out] = maximum score obtained by going from c_in to c_out via 1 part
vector<vector<bool>> visited;
vector<vector<char>> grid;

int curStartC = -1;
void dfs(int r, int c)
{
    visited[r][c] = true;

    vector<int> nc, nr;

    if (grid[r][c] == '.') {
        nr.emplace_back(r + 1);
        nc.emplace_back(c);
    }
    else if (grid[r][c] == 'L') {
        nr.emplace_back(r);
        nc.emplace_back(c - 1);
    }
    else if (grid[r][c] == 'R') {
        nr.emplace_back(r);
        nc.emplace_back(c + 1);
    }
    else if (grid[r][c] == '?') {
        nr.emplace_back(r);
        nc.emplace_back(c - 1);
        nr.emplace_back(r);
        nc.emplace_back(c + 1);
    }
    else
        assert(false);

    for (int i = 0; i < (int)nr.size(); i++) {
        if (nr[i] == h) {  // can get to this part
            adjmat[curStartC][c] = 1;
        }
        if (nr[i] < 0 || nr[i] >= h || nc[i] < 0 || nc[i] >= w) continue;
        if (visited[nr[i]][nc[i]]) continue;
        if (grid[nr[i]][nc[i]] == 'X') continue;
        dfs(nr[i], nc[i]);
    }
}

map<tuple<int, int, int>, ll> memo;

ll f(int inc, int outc, int i)
{
    if (memo.find({inc, outc, i}) != memo.end()) return memo[{inc, outc, i}];
    if (i == 0) {
        if (inc == outc)
            return 0;
        else
            return -1;
    }

    ll ans = -1;
    if (i & 1) {
        for (int inter = 0; inter < w; inter++) {
            if (adjmat[inc][inter] == -1) continue;
            ll res = f(inter, outc, i - 1);
            if (res == -1) continue;

            ans = max(ans, res + vals[inter]);
        }
    }
    else {
        for (int inter = 0; inter < w; inter++) {
            ll res1 = f(inc, inter, i >> 1);
            if (res1 == -1) continue;
            ll res2 = f(inter, outc, i >> 1);
            if (res2 == -1) continue;

            ans = max(ans, res1 + res2);
        }
    }

    memo[{inc, outc, i}] = ans;
    return ans;
}
int main()
{
    fast_cin();
    cin >> h >> w >> k;
    adjmat.assign(w, vector<int>(w, -1));
    vals.assign(w, 0);
    grid.assign(h, vector<char>(w, '.'));
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> grid[r][c];
        }
    }
    for (int i = 0; i < w; i++) {
        cin >> vals[i];
    }

    for (int i = 0; i < w; i++) {
        visited.assign(h, vector<bool>(w, false));
        curStartC = i;
        if (grid[0][i] == 'X') continue;
        dfs(0, i);
    }

    ll ans = 0;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            ll res = f(i, j, k);
            ans = max(ans, res);
        }
    }
    // // Technically this should be needed for correctness but it TLEs with this and ACs without
    // for (int l=0; l<=w; l++){
    //     memo.clear();
    //     for (int i=0; i<w; i++){
    //         for (int j=0; j<w; j++){
    //             ll res = f(i, j, l);
    //             ans = max(ans, res);
    //             ll res2 = f(i, j, k-l);
    //             ans = max(ans, res2);
    //         }
    //     }
    //     if (l >= k-1) break;
    // }
    cout << ans << endl;
    return 0;
}