/**Kattis - zebrasocelots
 * Observe that each bell basically represents incrementing a binary number where Z is 1 and O is 0
 * and the top of the stack is the MSB while the bottom is the LSB. So we just construct the binary
 * number then the answer is (2^n - 1 - x) where x is the binary number.
 * 
 * Time: O(n), Mem: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int main()
{
    int n;
    cin >> n;
    ll x = 0;
    for (int i = 0; i < n; i++) {
        x <<= 1LL;
        char c;
        cin >> c;
        x += (c == 'Z' ? 1 : 0);
    }
    cout << (1LL << n) - 1 - x << endl;
    return 0;
}