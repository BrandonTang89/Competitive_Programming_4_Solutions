/**Kattis - modulodatastructures
 * More or less follow the explanation in CP4 regarding square root decomposition. Observe
 * how we deal with the fact that n might not be a perfect square...
 * 
 * Time: O(q * sqrt(n)), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

int n, q;
vector<int> A;
vector<vector<int>> B;
int main(){
    cin >> n >> q;
    int sqrtn = ceil(sqrt(n));
    A.assign(n+1, 0);
    B.assign(sqrtn, vector<int>(sqrtn, 0));

    int a, b, c;
    while(q--){
        int t;
        cin >> t;
        if (t == 1){
            cin >> a >> b >> c;
            if (b >= sqrtn){
                for (int i=a; i<=n; i+=b){
                    A[i] += c;
                }
            }
            else{
                B[b][a] += c;
            }
        }
        else{
            cin >> a;
            int ans = A[a];
            for (int i=1; i<sqrtn; i++){
                ans += B[i][a%i];
            }
            cout << ans << endl;
        }
    }
    return 0;
}