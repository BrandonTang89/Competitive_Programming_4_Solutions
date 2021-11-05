/* Kattis - cokolada
Observation 1:
    Well obviously the size of chocolate we need is 2^n where 2^(n-1) < x <= 2^n.
    As for how many cuts we need... note that the greedy algorithm of breaking 2^n into half
    and breaking one side into half recursively until x can be made is optimal.
    So how many cuts do we need? The answer is the number of binary digits used
    to represent x - the number of trailing zeros of x.

Time: O(1), Space: O(1)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;
 
typedef long long ll;
typedef long double ld;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int x, n;
int main(){
    cin >> x;
    n = (1 << (int) ceil(log2(x)));
    cout << n << " ";
    int y = ceil(log2(x)) - __builtin_ctz(x);

    cout << y << endl;

    return 0;
}
