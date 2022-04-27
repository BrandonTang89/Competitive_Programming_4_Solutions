/**Kattis - granica
 * Honestly not too sure what this has to do with CRT, but here we just notice that M | xi - xj
 * for all ordered pairs i, j. As such, M | gcd( xi - xj for all i, j). So we just compute that
 * GCD and then we get all divisors of that.
 * 
 * Time: O(n^2 + sqrt(gcd)), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
vector<ll> v;
vector<ll> getfactors(ll n) {
    vector<ll> factors;
    for (ll i = 1; i <= (int)sqrt(n); i++) {
        if (n % i == 0) {  // i is a factor and n/i is a factor
            factors.emplace_back(i);
            factors.emplace_back(n / i);
        }
    }

    if (floor(sqrt(n)) * floor(sqrt(n)) == n) {  // n is a perfect square
        factors.pop_back();
    }
    return factors;
}
int main(){
    cin >> n;
    v.resize(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    ll ans = 0;
    for (int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){
            ans = gcd(ans, abs(v[i]-v[j]));
        }
    }
    auto factors = getfactors(ans);
    sort(factors.begin(), factors.end());
    for (auto f : factors){
        if (f == 1)continue;
        cout << f << " ";
    }
    cout << endl;

    return 0;
}