// UVa 1709 Amagamated Artichokes - Accepted
// Single pass on array with time O(n) and memory O(n). Memory usage could be reduced to O(1) by calculating the price values on the fly.
// Note the use of "setprecision" to increase the number of signficant figures printed at cout

#include <bits/stdc++.h>
using namespace std;


long double price(int p, int a, int b, int c, int d, int k){
    return (long double) p*(sin(a * k + b) + cos(c * k + d) + 2);
}

long double prices[1000009];
int main(){
    int p, n, a, b, c, d;
    cout << setprecision(16);
    while (cin >> p){
        cin >> a >> b >> c >> d >> n;

        long double max_decline;
        max_decline = 0;
        
        for (int i=1; i<= n; i++){
            prices[i] = price(p,a,b,c,d,i);
        }

        long double max_prev = prices[1];
        for (int i=2;i<=n; i++){
            max_decline = max(max_decline, max_prev - prices[i]);
            max_prev = max(max_prev, prices[i]);
        }

        cout << max_decline << endl;
    }

    return 0;
}