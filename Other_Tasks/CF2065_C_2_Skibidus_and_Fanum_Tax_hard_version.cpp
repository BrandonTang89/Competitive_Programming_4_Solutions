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
        vector<ll> a(n), b(m);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }  
        for (int i = 0; i < m; i++){
            cin >> b[i];
        }

        sort(b.begin(), b.end());
        ll prev = -1e12;
        bool can = true;
        for (int i=0; i<n; i++){
            int idx  = lower_bound(b.begin(), b.end(), a[i] + prev) - b.begin();
            ll cur = (idx == m) ? 1e12 : b[idx] - a[i];
            if (a[i] < cur && a[i] >= prev){
                cur = a[i];
            }

            if (cur == 1e12){
                cout << "NO" << endl;
                can = false;
                break;
            }
            else{
                prev = cur;
            }
        }

        if (can){
            cout << "YES" << endl;
        }
    }

    return 0;
}