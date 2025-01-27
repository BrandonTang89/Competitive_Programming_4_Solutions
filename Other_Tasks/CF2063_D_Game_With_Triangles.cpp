#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int an, bn;
vector<ll> arr, brr;
vector<ll> pfsa, pfsb; // pfsa[i] is the the sum of the best i pairs of arr=


ll value(int fromA, int k){
        int fromB = k - fromA;
        return pfsa[fromA] + pfsb[fromB];
}

int main(){
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--){
        cin >> an >> bn;
        arr.resize(an);
        brr.resize(bn);

        for (int i = 0; i < an; i++){
            cin >> arr[i];
        }
        for (int i = 0; i < bn; i++){
            cin >> brr[i];
        }

        sort(arr.begin(), arr.end());
        sort(brr.begin(), brr.end());

        pfsa.assign(an + 1, -1e9);
        pfsb.assign(bn + 1, -1e9);
        pfsa[0] = 0;
        pfsb[0] = 0;

        for (int i=0,j=an-1; i<j; i++,j--){
            pfsa[i+1] = pfsa[i] + arr[j] - arr[i];
        }

        for (int i=0,j=bn-1; i<j; i++,j--){
            pfsb[i+1] = pfsb[i] + brr[j] - brr[i];
        }

        vector<ll> ans;
        for (int k=1;;k++){
            ll hi = min(k, an-k);
            ll lo = max(0, 2*k-bn);

            if (hi < lo){
                break;
            }

            // Ternary search for the best value of i, find maximum
            while (lo + 5 < hi){
                int m1 = lo + (hi - lo) / 3;
                int m2 = hi - (hi - lo) / 3;

                if (value(m1, k) < value(m2, k)){
                    lo = m1;
                } else {
                    hi = m2;
                }
            }
            
            ll best = -1e18;
            for (int i = lo; i <= hi; i++){
                best = max(best, value(i, k));
            }
            ans.push_back(best);

        }
        cout << ans.size() << endl;
        for (auto x: ans){
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}