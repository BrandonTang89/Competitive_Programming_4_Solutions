#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);



int main(){
    int tc;
    cin >> tc;
    while (tc--){
        int n, m;
        cin >> n >> m;
        vector<vector<ll>> a(n, vector<ll>(m));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> a[i][j];
            }
        }
        vector<ll> sums(n);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                sums[i] += a[i][j];
            }
        }

        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 0);
        sort(perm.begin(), perm.end(), [&](int i, int j){
            return sums[i] > sums[j];
        });

        vector<ll> total; 
        for (int i=0; i<n; i++){
            for (int j=0; j<m; j++){
                total.push_back(a[perm[i]][j]);
            }
        }

        ll prefix = 0;
        ll total_sum = 0;
        for (int i=0; i<n*m; i++){
            prefix += total[i];
            total_sum += prefix;
        }

        cout << total_sum << endl;
    }


    return 0;
}