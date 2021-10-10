/* Kattis - permutedarithmeticsequence

Simply compare adjacent elements to determine if there exist a common difference. Sort and do check again if the sequence
is not arithmetic.

Time: O(n log n), Mem: O(n)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int t, n;
int arr[101];

bool arithmetic(int arr[101]) {
    int diff = arr[1] - arr[0];
    for (int i = 2; i < n; i++) {
        if ((arr[i] - arr[i - 1]) != diff) return false;
    }
    return true;
}

int main() {
    cin >> t;
    for (int tc = 0; tc < t; tc++) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        if (arithmetic(arr)) {
            cout << "arithmetic" << endl;
            continue;
        }

        sort(arr, arr + n);
        if (arithmetic(arr)) {
            cout << "permuted arithmetic" << endl;
            continue;
        }

        else
            cout << "non-arithmetic" << endl;
    }

    return 0;
}