#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
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
        ll n;
        cin >> n;

        if (__builtin_popcountll(n) == 1){
            cout << 1 << endl << n << endl;
            continue;
        }

        cout << __builtin_popcountll(n) + 1 << endl;
        for (int i=63; i>=0; i--){
            if (n & (1LL << i)){
                cout << (n^(1LL << i)) << " ";
            }
        }

        cout << n << endl;
        

    }

    return 0;
}