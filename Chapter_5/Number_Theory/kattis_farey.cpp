/**Kattis - farey
 * The task statement is trying to scare you with talks about a sequence. Since we only care about the
 * number of fractions, the order doesnt matter. Now for all possible fractions a/b, we should only
 * count it if gcd(a,b) = 1, ie the fraction is in its simplest form. This ensures no double counting
 * and it is trivial to see that the simplest form will be part of the count somewhere else.
 * 
 * Note that for all fractions in the from a/b, for each b > 2, the number of irreductable fractions is
 * phi(b) where phi is the totient function. Thus, we want to sum phi(i) for all i from 2 to n. then
 * we add 2 for 0/1 and 1/1. This can be precomputed and we can use static range queries.
 * 
 * Time: O(n log log n + q)
 * Space: O(n)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

vector<int> EulerPhi;
/**fillEulerPhi computes the Euler's Totient Function
 * @param _upperbound: compute for all numbers in [0, _upperbound]
 * EulerPhi[i] = number of integers j in [0, i] such that gcd(i, j) = 1
 */
void fillEulerPhi(int _upperbound) {
    EulerPhi.assign(_upperbound + 1, 0);
    for (int i = 1; i <= _upperbound; i++) {
        EulerPhi[i] = i;
    }
    for (int i = 2; i <= _upperbound; i++) {
        if (EulerPhi[i] == i) {  // i is prime
            for (int j = i; j <= _upperbound; j += i) {
                EulerPhi[j] = EulerPhi[j] / i * (i - 1);  // i is aprime factor of j
            }
        }
    }
}

vector<int> static_range_sum;

int main() {
    fast_cin();
    fillEulerPhi(10009);
    static_range_sum.assign(10005, 0);
    static_range_sum[1] = 2;

    for (int i = 2; i <= 10004; i++) {
        static_range_sum[i] = static_range_sum[i - 1] + EulerPhi[i];
    }

    int n, case_num, q;
    cin >> n;

    for (int c = 0; c < n; c++) {
        cin >> case_num;
        cin >> q;

        cout << case_num << " " << static_range_sum[q] << endl;
    }

    return 0;
}
