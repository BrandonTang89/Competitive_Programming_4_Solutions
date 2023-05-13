/**Kattis - pikemaneasy
 * We first observe that the optimal stategy is to do the problems in increasing order of time
 * taken.
 * This is all we need for the easy version. Note the existance of pikemanhard.
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n;
ll t;
ll a, b, c;
vector<int> arr;
int main()
{
    cin >> n >> t;
    cin >> a >> b >> c;
    arr.assign(n, 0);
    int ti;
    cin >> ti;
    arr[0] = ti;

    for (int i = 1; i < n; i++) {
        ti = (a * ti + b) % c + 1LL;
        arr[i] = ti;
    }
    sort(arr.begin(), arr.end());
    ll timeTaken = 0;
    ll totalPenalty = 0;
    for (int i = 0; i < n; i++) {
        timeTaken += arr[i];
        if (timeTaken > t) {
            cout << i << " " << totalPenalty << endl;
            return 0;
        }
        totalPenalty += timeTaken;
        totalPenalty %= ((ll)1e9 + 7);
    }
    cout << n << " " << totalPenalty << endl;

    return 0;
}