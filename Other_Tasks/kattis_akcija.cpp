#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, c;
vector <int> v;
int main(){
    cin >> n;
    for (int i=0; i<n; i++){
        cin >> c;
        v.push_back(c);
    }
    sort(v.begin(), v.end(), greater<int>());
    int ans = 0;
    for (int i=0; i< (int) v.size(); i++){
        if ((i+1) % 3 == 0)continue;
        ans += v[i];
    }

    cout << ans << endl;

    return 0;
}