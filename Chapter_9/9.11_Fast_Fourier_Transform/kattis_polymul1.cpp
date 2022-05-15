/**Kattis - polymul1
 * The basic O(n^2) polynomial multiplication algorithm.
 * 
 * Time: O(n^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int num_tc;
int main(){
    fast_cin();
    cin >> num_tc;
    while (num_tc--){
        int n, m;
        cin >> n;
        n++;
        vector<int> f(n);
        for (int i = 0; i < n; i++) cin >> f[i];
        cin >> m;
        m++;
        vector<int> g(m);
        for (int i = 0; i < m; i++) cin >> g[i];

        vector<int> ans(n+m-1, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ans[i+j] += f[i] * g[j];
        
        cout << n+m-2 << endl;
        for (int i = 0; i < n+m-1; i++)
            cout << ans[i] << " ";
        cout << endl;
    }

    return 0;
}