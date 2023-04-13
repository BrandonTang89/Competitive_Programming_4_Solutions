/**Kattis - sumandproduct
 * Basically adhoc. For each index i, we find the number of solutions ending at i (inclusively). The
 * naive way to do this would be O(n) resulting in O(n^2) time overall. However, we notice that
 * multiplication grows very quickly, and once the product exceeds the sum v[0, i] we can exit
 * early.
 *
 * But, with a lot of 1s, we could still end up checking O(n) solutions for each i. But if we
 * compress contiguous 1s into a single 1 (with extra information on how many 1s exist in the
 * block), at the worst case, our multiplication product (v[i-k] * v[i-k+1] * ... * v[i]) doubles
 * every 2 elements considered resulting in checking at most O(log sum(v[0, i])) solutions for each
 * i.
 *
 * Time: O(n log sum(v[0, n-1])), Mem: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
vector<int> v, num_ones;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int no = 0;
        while (i < n && x == 1) {
            no++;
            i++;
            cin >> x;
        }
        if (no > 0) {
            v.push_back(1);
            num_ones.push_back(no);
        }
        if (x > 1) {
            v.push_back(x);
            num_ones.push_back(0);
        }
    }

    n = v.size();
    ll ans = 0;
    ll total = 0;
    for (int i = 0; i < n; i++) {
        total += max(v[i], num_ones[i]); // sum of all elements in v[0, i]

        // if num_ones[i] != 0
        for (int k = 0; k < num_ones[i]; k++) {  // we start from any part inside a block of 1s
            ll cursum = k + 1;
            ll curmult = 1;
            for (int j = i - 1; j >= 0; j--) {
                curmult *= v[j];
                if (curmult > total) break;

                if (v[j] != 1) {
                    cursum += v[j];
                    if (cursum == curmult) {
                        ans++;
                    }
                }
                else {
                    if (cursum < curmult && cursum + num_ones[j] >= curmult) {
                        ans++;
                    }
                    cursum += num_ones[j];
                }
            }
        }

        if (num_ones[i] == 0) {
            ll cursum = v[i];
            ll curmult = v[i];
            for (int j = i - 1; j >= 0; j--) {
                curmult *= v[j];
                if (curmult > total) break;

                if (v[j] != 1) {
                    cursum += v[j];
                    if (cursum == curmult) {
                        ans++;
                    }
                }
                else {
                    if (cursum < curmult && cursum + num_ones[j] >= curmult) {
                        ans++;
                    }
                    cursum += num_ones[j];
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}