/* Kattis - neighbourhoodwatch
This question requires somewhat fast IO, so C++ is the way to go. Notice that for each
house i, the number of safe walks starting from i is equal to n - (the closest safe house > i)
or 0 if there are no further safe houses. This gives an O(n) solution. We can improve this to O(k)
by determining the number of houses between each safe house. Note the use of the axuiliary -1 safe house.

Time: O(k), Space: O(k)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
ll n, k, h;
vector<ll> safe;
int main(){
    scanf("%lld %lld", &n, &k);
    safe.emplace_back(-1);
    for (int i=0;i<k;i++){
        scanf("%lld", &h);
        h--;
        safe.emplace_back(h);
    }

    ll total = 0;
    for (int i=1;i<k+1;i++){
        total += (n - safe[i]) * (safe[i] - safe[i-1]); 
        // (safe[i] - safe[i-1]) houses between safe house i and the previous safe house
        // , counting i but not the previous house
        // (n - safe[i]) houses from safe house i and the end of the street
    }
    
    printf("%lld\n", total);

    return 0;
}