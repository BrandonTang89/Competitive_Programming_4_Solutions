#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


int n;
vector<int> a;
int main(){
    int tc;
    cin >> tc;
    while(tc--){
        cin >> n;
        a.resize(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }

        int ans = 1;
        for (int k=0; k<20; k++){
            
            int forThis = 0;
            int i = 0, prev = -1;
            while (i < n){
                while (i < n && (a[i] & (1 << k)) == 0){
                    i++;
                }
                // kth bit of i is one
                forThis = max(forThis, i - prev);
                prev = i;
                i++;
            }

            if (forThis != n+1){
                ans = max(ans, forThis);
            }
        }

        cout << ans << endl;
    }

    return 0;
}