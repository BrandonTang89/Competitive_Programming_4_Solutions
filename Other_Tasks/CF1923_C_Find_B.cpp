#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, q;
vector<ll> a, num1s, presum; // num1s[i] = number of 1s in a[0..i]

ll q1s(int l, int r){
    // return number of 1s in a[l..r]
    return num1s[r] - (l > 0 ? num1s[l-1] : 0);
}
ll qsum(int l, int r){
    // return sum of a[l..r]
    return presum[r] - (l > 0 ? presum[l-1] : 0);
}

int main(){
    int tc;
    cin >> tc;
    while (tc--){
        cin >> n >> q;
        a.resize(n);
        for (int i=0; i<n; i++){
            cin >> a[i];
        }
        num1s.assign(n, 0);
        presum.assign(n, 0);

        for (int i=0; i<n; i++){
            num1s[i] = (a[i] == 1) + (i > 0 ? num1s[i-1] : 0LL);
            presum[i] = a[i] + (i > 0 ? presum[i-1] : 0LL);
        }

        while(q--){
            int l, r;
            cin >> l >> r;
            l--; r--;

            ll necessary = q1s(l, r) + (r-l+1);
            ll have = qsum(l, r);

            if (necessary > have || (l == r)){
                cout << "NO\n";
            }
            else{
                cout << "YES\n";
            }
        }


    }

    return 0;
}