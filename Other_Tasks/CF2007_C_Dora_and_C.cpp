#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


int main(){
    int t;
    cin >> t;
    while (t--){
        int n, a, b;
        cin >> n >> a >> b;
        vector<int> v(n);
        for (int i = 0; i < n; i++){
            cin >> v[i];
        }

        int d = gcd(a, b);
        set<int> s;
        for (int i = 0; i < n; i++){
            s.insert(v[i]%d);
        }

        if (s.size() == 0){
            cout << 0 << endl;
            continue;
        }

        int biggestGap = *s.begin() + (d - 1 - *s.rbegin());
        for (auto it = s.begin(); it != --s.end(); it++){
            biggestGap = max(biggestGap, *next(it) - 1 - *it);
        }

        cout << d - 1 - biggestGap << endl;

    }

    return 0;
}