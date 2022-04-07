/**Kattis - cranes
 * Simple enough complete search problem. We use an interative bitmask technique to check all 2^n subsets of
 * cranes. For each subset, use a k^2 where k is the subset size check to ensure that the subset is valid.
 * 
 * Time: O(2^n * n^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define LSOne(S) (S & (-S))
int n;
vector<tuple<int, int, int>>v;
int main(){
    int num_tc;
    cin >> num_tc;
    while (num_tc--){
        cin >> n;
        v.resize(n);
        for (int i = 0; i < n; i++){
            int a, b, c;
            cin >> a >> b >> c;
            v[i] = make_tuple(a, b, c);
        }

        int ans = 0;
        for (int bm=0; bm<(1<<n); bm++){
            bool valid = true;
            int cur = 0;
            for (int m=bm; m && valid; m-=LSOne(m)){
                for (int q=m-LSOne(m); q; q-=LSOne(q)){
                    int a = __builtin_ctz(m);
                    int b = __builtin_ctz(q);

                    auto &[x1, y1, r1] = v[a];
                    auto &[x2, y2, r2] = v[b];

                    if ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) <= (r1+r2)*(r1+r2)){
                        valid = false;
                        break;
                    }
                }
                auto &[x, y, r] = v[__builtin_ctz(m)];
                cur += r*r;
            }

            if (valid){
                ans = max(ans, cur);
            }
        }
        cout << ans << endl;
    }

    return 0;
}