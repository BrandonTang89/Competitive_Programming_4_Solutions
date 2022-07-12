/**Kattis - financialplanning
 * Just BSTA. Observe that the max time possible ever is with the max M 1e9 and worse investment which requires
 * 1e9 money and gives back 1 money, resulting in 2*1e9 time.
 * 
 * Time: O(n log (1e10)), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

ll n, m;
vector<tuple<ll, ll>> v; // (p, c)

bool works(ll days){
    ll total = 0;
    for (auto &[p, c]: v){
        total += max((p*days) - c, 0LL);
        if (total >= m) return true;
    }
    return false;
}
int main(){
    fast_cin();
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int p, c;
        cin >> p >> c;
        v.emplace_back(p, c);
    }

    ll L = 0, R = 1e10, mid;
    while (L + 1 < R){
        mid = (L + R) / 2;
        if (works(mid)){
            R = mid;
        }
        else{
            L = mid + 1;
        }
    }
    if (works(L)){
        R = L;
    }
    
    cout << R << endl;

    return 0;
}