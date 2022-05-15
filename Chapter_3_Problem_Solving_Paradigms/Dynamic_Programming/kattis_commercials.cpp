/* Kattis - commercials

This is kadane but with applying -p to all elements since taking up that slot incurs p cost and provides
a[i] extra money, resulting in a[i]-p profit.

Time: O(n), Mem: O(1)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
 
int n, p;
int sum = 0, ans = 0, cur;
int main(){
    fast_cin();
    cin >> n >> p;

    for (int i=0;i<n;i++){
        cin >> cur;
        cur -= p;
        sum += cur;
        ans = max(ans, sum);
        sum = max(sum, 0);
    }
    
    cout << ans << endl;
    
    
    return 0;
}