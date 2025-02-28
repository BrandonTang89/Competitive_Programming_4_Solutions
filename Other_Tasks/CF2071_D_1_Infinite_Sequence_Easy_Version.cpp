#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

template <typename T=int>
struct StaticSum {
    const int n;
    vector<T> pfs;  // arr[i] contains the range sum from 0 to i inclusively

    T rsq(int l, int r) const {            // range sum from l to r inclusively
        if (l < 0 || r >= n) assert(false);  // boundary condition check
        if (l == 0) return pfs[r];
        return (pfs[r] ^ pfs[l - 1]);
    }

    StaticSum(const vector<T>& arr) : n(arr.size()), pfs(arr) {
        for (int i = 1; i < n; i++) {
            pfs[i] ^= pfs[i - 1];
        }
    }
};


int main(){
    int tc;
    cin >> tc;
    while (tc--){
        int n;
        ll q;
        cin >> n >> q >> q;
        vector<int> v(n+1);
        for (int i=0; i<n; i++){
            cin >> v[i+1];
        }
        

        if (n%2 == 0){ // make n odd
            int acc = 0;
            for (int i=1;i<=n/2; i++){
                acc ^= v[i];
            }
            v.emplace_back(acc);
            n++;
        }

        StaticSum<int> ss(v);
        
        int ans = 0;
        while (q > 0){
            if (q <= n){
                cout << (v[q] ^ ans) << endl;
                break;
            }
            else if (q / 2LL <= n){
                cout << (ss.rsq(1, q/2LL) ^ ans) << endl;
                break;
            }
            else if ((q / 2LL) %2 == 1){
                cout << (ss.rsq(1, n) ^ ans) << endl;
                break;
            } 
            else{
                q = (q/2LL);
                ans ^= ss.rsq(1, n);
            }
        }


    }


    return 0;
}