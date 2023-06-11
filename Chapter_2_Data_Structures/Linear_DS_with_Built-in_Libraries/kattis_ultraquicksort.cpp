/**Kattis - ultraquicksort
 * Just count the number of inversions, simple with merge sort with book keeping.
 * Time: O(n log n), Space: O(n)
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

int n;
vector<int> a, b;
ll numInver = 0;

void merge(int l, int r)
{                            // sort a[l, r)
    if (l + 1 >= r) return;  // singleton or empty
    int m = (l + r) / 2;
    merge(l, m);
    merge(m, r);

    // merge
    int i = l, j = m;
    b.clear();
    while (i < m && j < r) {
        if (a[i] <= a[j]) {
            b.push_back(a[i]);
            i++;
        }
        else {
            b.push_back(a[j]);
            j++;
            numInver += m - i;
        }
    }
    while (i < m) {
        b.push_back(a[i]);
        i++;
    }
    while (j < r) {
        b.push_back(a[j]);
        j++;
    }
    for (int i = l; i < r; i++) {
        a[i] = b[i - l];
    }
}
int main()
{
    fast_cin();
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    merge(0, n);
    cout << numInver << endl;
    return 0;
}