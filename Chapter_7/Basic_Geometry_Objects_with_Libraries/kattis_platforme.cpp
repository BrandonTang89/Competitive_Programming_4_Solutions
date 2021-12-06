/**Kattis - Platforme
 * Could be solved with computational geometry techniques. But im very tired, and we can
 * just use brute force since the constraints are small... So that's what we will
 * roll with!
 * 
 * Time: O(n*10000*2), Space: O(10000)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, y, s, e;
bool used[10009][10009], platform[10009][10009];
tuple<int, int, int> platforms[109];
ll ans = 0;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> y >> s >> e;
        platforms[i] = make_tuple(y, s, e);
    }
    sort(platforms, platforms + n);
    for (int i = 0; i < n; i++) {
        auto &[y, s, e] = platforms[i];
        for (int j = y; j > 0; j--) {
            if (platform[j][s] == true) {
                break;
            }

            used[j][s] = true;
            ans++;
        }
        for (int j = y; j > 0; j--) {
            if (platform[j][e-1] == true) {
                break;
            }

            used[j][e-1] = true;
            ans++;
        }
        for (int j = s; j < e; j++) {
            platform[y][j] = true;
        }
    }
    /*
    for (int i=100; i >= 1; i--) {
        for (int j=1; j < 100; j++){
            cout << used[i][j] << " ";
        }
        cout << endl;
    }*/
    cout << ans << endl;

    return 0;
}