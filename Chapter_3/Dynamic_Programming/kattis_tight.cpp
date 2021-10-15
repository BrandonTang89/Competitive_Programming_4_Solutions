/* Kattis - tight
Relatively easy DP question. 

State: Current last digit, number of remaining digits
Base case:
    invalid last digit, 0 remaining digits
Transition: one digit up, same last digit or one digit down

Time: O(nk), Mem: O(nk)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long double ld;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int k, n;
ld memo[11][109];
ld dp(int c, int rn){ // current latest digit, remaining digits
    if (c < 0 || c > k)return 0; // invalid
    if (rn == 0)return 1; // valid and finished
    ld &ans = memo[c][rn]; 
    if (ans != -1)return ans;

    ans = 0;
    ans += dp(c-1, rn-1) + dp(c, rn-1) + dp(c+1, rn-1);

    return ans;
}

int main(){
    cout.precision(std::numeric_limits<double>::digits10);
    while (scanf("%d %d", &k, &n) != EOF){
        memset(memo, -1, sizeof(memo));
        ld total = pow(k+1, n);
        ld ans = 0;
        for (int i=0;i<=k;i++){
            ans += dp(i, n-1);
        }
        cout << ans*100/total << endl;
    }

   return 0;
}