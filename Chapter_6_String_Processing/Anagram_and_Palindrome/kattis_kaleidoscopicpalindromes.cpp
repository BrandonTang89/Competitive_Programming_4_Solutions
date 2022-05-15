/**Kattis - kaleidoscopicpalindromes
 * We use a complete search solution, this is alright since a siginificant number of numbers won't even
 * be a binary palindrome, let alone a ternary palindrome etc etc. Note that we can compare the digits
 * of a number in a different base without the overhead of actually converting it into a vector.
 * 
 * Specifically, the ith digit of n in base b is (n / b^(i-1)) % b.
 * 
 * Time: O(? kinda output dependant), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll fexp(ll b, ll p) {
    if (p == 0) return 1;

    ll ans = fexp(b, p >> 1);
    ans = ans * ans;
    if (p & 1) ans = ans * b;
    return ans;
}

bool isPalindrome(int n, int base) {
    int num_digits = log(n) / log(base) + 1;
    for (int i = 1; i <= num_digits / 2; i++) {
        if ((n % base) != ((n / fexp(base, num_digits - 2 * i + 1)) % base)) {
            // check corresponding digits
            return false;
        }
        n /= base;
    }
    return true;
}

int main() {
    int l, r, b, ans = 0;
    bool pali;
    cin >> l >> r >> b;
    for (int i = l; i <= r; i++) {
        pali = true;
        for (int j = 2; j <= b; j++) {
            if (!isPalindrome(i, j)) {
                pali = false;
                break;
            }
        }
        if (pali) {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}