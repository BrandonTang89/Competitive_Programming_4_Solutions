/**Kattis - cropeasy
 * Easy problem. Just for each distinct selection of 3 trees, check if the center is a grid point.
 * Use long long to prevent overflow.
 * 
 * Time: O(n^3), Space: O(n^3)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

ll num_tc, n, A, B, C, D, x0, yo, M;
vector<pair<ll,ll>> tree;

int main(){
    cin >> num_tc;
    for(int tc=1; tc<= num_tc;tc++){
        cin >> n >> A >> B >> C >> D >> x0 >> yo >> M;
        tree.clear();
        tree.push_back({x0, yo});

        for (int i=1; i<n; i++){
            ll x = (A * tree[i-1].first + B) % M;
            ll y = (C * tree[i-1].second + D) % M;
            tree.push_back({x, y});
        }

        int ans = 0;
        for (int i=0; i<n; i++){
            for (int j=i+1;j<n; j++){
                for (int k=j+1; k<n; k++){
                    ll sum_x = tree[i].first + tree[j].first + tree[k].first;
                    ll sum_y = tree[i].second + tree[j].second + tree[k].second;

                    if (sum_x % 3 || sum_y % 3){
                        continue;
                    }
                    ans++;
                }
            }
        }
        printf("Case #%d: %d\n", tc, ans);
    }
    return 0;
}