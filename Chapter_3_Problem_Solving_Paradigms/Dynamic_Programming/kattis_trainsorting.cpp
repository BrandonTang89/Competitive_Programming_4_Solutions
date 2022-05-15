/**Kattis - trainsorting
 * Consider an optimal train. Let car i be the first car coming into the station that is part of the
 * optimal train. The length of the optimal train is the LIS + LDS - 1 from car i. For all cars in
 * the LIS, they are appended to the front while all cards in the LDS are appended to the back. If
 * we iterate overall possible cars i, we will eventually get the highest answer since the optimal
 * train has at least 1 car.
 * 
 * Observe that the LIS starting from car i is the length of the LDS of the reverse vector of cars
 * ending at car i. Similarly, the LDS starting from car i is the LIS of the reverse vector ending at
 * car i. Since it is easier to compute the LIS and LDS ending at a particular element, we reverse
 * the vector and then compute LDS and LIS ending at each element and then comparing LDS(i) + LIS(i)-1
 * with our candidate maximum answer, updating it as we go to find the global max.
 * 
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
int main() {
    fast_cin();
    cin >> n;
    vector<int> v;      // Original array
    vector<int> v_dec;  //

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);
        v_dec.push_back(-x);
    }
    reverse(v_dec.begin(), v_dec.end());
    reverse(v.begin(), v.end());
    vector<int> L(n, 0);  // L[i] is the minimum last element of an IS of length i
    vector<int> L_dec(
        n, 0);  // L_dec[i] is the maximum last element of a decreasing sequence of length i
    int k = 0, k_dec = 0;  // length of current LIS

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(L.begin(), L.begin() + k, v[i]) - L.begin();
        L[pos] = v[i];
        if (pos == k) {
            k++;
        }

        int pos_dec = lower_bound(L_dec.begin(), L_dec.begin() + k_dec, v_dec[i]) - L_dec.begin();
        L_dec[pos_dec] = v_dec[i];
        if (pos_dec == k_dec) {
            k_dec++;
        }

        ans = max(ans, pos + pos_dec + 1);
    }
    cout << ans << endl;

    return 0;
}