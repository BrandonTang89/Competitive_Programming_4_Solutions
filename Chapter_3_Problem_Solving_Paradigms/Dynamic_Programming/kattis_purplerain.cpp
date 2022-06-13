/**Kattis - purplerain
 * Kadane with printing optimal solution. Notice that since we want the maximum difference, we can
 * break down the problem into two subproblems: find the subarray that maximised num red - num blue
 * and find the subarray that maximised num blue - num red. So we just make 2 arrays, replacing R
 * with 1 and B with -1 and then vice versa. Then we can use Kadane's algorithm, keeping track of
 * the location of the optimal solution.
 *
 * Then we just merge the two subproblems and print the optimal solution.
 * 
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
tuple<int, int, int> kadane(vector<int> &A) {
    ll sum = 0, ans = 0;
    int anss = 0, anse = 0, s = 0;
    for (int i = 0; i < n; ++i) {  // linear scan, O(n)
        sum += A[i];               // greedily extend this

        if (sum > ans) {
            ans = sum;
            anss = s;
            anse = i;
            continue;
        } else if (sum == ans) {
            continue;  // we'll take the left most anyway
        }

        if (sum < 0) {
            sum = 0;  // reset the running sum
            s = i + 1;
        }
    }
    return {ans, anss, anse};
}
string s;
vector<int> v;
int main() {
    cin >> s;
    n = s.size();
    v.resize(n);
    for (int i = 0; i < n; ++i) {
        v[i] = (s[i] == 'B') ? -1 : 1;
    }
    auto ans = kadane(v);
    for (int i = 0; i < n; ++i) {
        v[i] = -1 * v[i];
    }
    auto ans2 = kadane(v);

    auto &[val1, s1, e1] = ans;
    auto &[val2, s2, e2] = ans2;
    s1++;
    e1++;
    s2++;
    e2++;

    if (val1 > val2) {
        cout << s1 << " " << e1 << endl;
    } else if (val1 < val2) {
        cout << s2 << " " << e2 << endl;
    } else {
        if (make_pair(s1, e1) < make_pair(s2, e2)) {
            cout << s1 << " " << e1 << endl;
        } else {
            cout << s2 << " " << e2 << endl;
        }
    }
    return 0;
}