/**KackerRank Problem Solving Intermediate Question 1
 * Given an array of integers, let f(i) be the folling function:
 *  1. Take the first i numbers and sort them in ascending (non-decreasing) order to get a new array S
 *  2. f(i) = S[1]*1 + S[2]*2 + ... + S[i]*i
 * 
 * Task: Given an array A of length n, calculate f(1) + f(2) + ... + f(n) mod 1000000007
 * 
 * Input Format: Array of integers a of length n
 * Output Format: Sum of f(1) + f(2) + ... + f(n) {as an integer}
 * 
 * Constraints: 
 * 1 <= n <= 10^5
 * 1 <= A[i] <= 10^6
 * 
 * Sample Input:
 * a = {4, 3, 2, 1}
 * 
 * Sample Output:
 * 65
 * 
 * Solution:
 * We can use a multiset to simulate the process, using the following relationship:
 * f(i-1) = f(i) - num_of_elements_before_A[i] * A[i] - range_sum_of_everything_past_A[i]
 * 
 * However, this is slow since the range_sum is O(n) per query, resulting in overall O(n^2) time.
 * 
 * We can use fenwick trees to solve this problem in O(n log n). The solution is that we start with a fenwick tree that has A in sorted order.
 * Then, for each i in [n-1, 0] we remove A[i] from the fenwick tree and compute the range sum of everything past A[i] in log n. To get the
 * number of elements before A[i], we can use another fenwick tree that only has ones and zeros to represent whether an element is still in the 
 * set or not. To know the index of the fenwick tree where a certain element A[i] is at, we use a hashmap to map A[i] to its index. Since A[i]
 * might not be unique, each A[i] can have multiple consecutive indices. We can deal with this by only storing the last index and decrementing
 * m[A[i]] eachtime we remove each A[i] from the fenwick tree.
 * 
 * Time: O(n log n), Space: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))                    // the key operation

typedef long long ll;                            // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

ll mod(ll a, ll b) {
    ll r = a % b;
    return r < 0 ? r + b : r;
}
class FenwickTree {                              // index 0 is not used
private:
  vll ft;                                        // internal FT is an array
public:
  FenwickTree(int m) { ft.assign(m+1, 0); }      // create an empty FT

  void build(const vll &f) {
    int m = (int)f.size()-1;                     // note f[0] is always 0
    ft.assign(m+1, 0);
    for (int i = 1; i <= m; ++i) {               // O(m)
      ft[i] += f[i];                             // add this value
      if (i+LSOne(i) <= m)                       // i has parent
        ft[i+LSOne(i)] += ft[i];                 // add to that parent
    }
  }

  FenwickTree(const vll &f) { build(f); }        // create FT based on f

  FenwickTree(int m, const vi &s) {              // create FT based on s
    vll f(m+1, 0);
    for (int i = 0; i < (int)s.size(); ++i)      // do the conversion first
      ++f[s[i]];                                 // in O(n)
    build(f);                                    // in O(m)
  }

  ll rsq(int j) {                                // returns RSQ(1, j)
    ll sum = 0;
    for (; j; j -= LSOne(j))
      sum += ft[j];
    return sum;
  }

  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // inc/exclusion

  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
  void update(int i, ll v) {
    for (; i < (int)ft.size(); i += LSOne(i))
      ft[i] += v;
  }

  int select(ll k) {                             // O(log m)
    int p = 1;
    while (p*2 < (int)ft.size()) p *= 2;
    int i = 0;
    while (p) {
      if (k > ft[i+p]) {
        k -= ft[i+p];
        i += p;
      }
      p /= 2;
    }
    return i+1;
  }
};


map<int, int> m; // m[i] = the index of the FT with i 
const ll MOD = (int) 1e9 + 7;
int sortedSum(vector<int> a) {
    int n = a.size();
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());

    FenwickTree ft(n);
    FenwickTree ft2(n);
    for (int i = 1; i <= n; ++i) {
        m[sorted_a[i-1]] = i;
        ft.update(i, sorted_a[i-1]);
        ft2.update(i, 1);
    }
    
    ll cur = 0;
    for (int i=1; i<=n; i++){
        cur += (i * ft.rsq(i, i))%MOD;
        cur %= MOD;
    }
    
    ll ans = cur;
    for (int i=n-1; i>=0; i--){
        // cout << "ai " << a[i] << " mai" << m[a[i]] << endl;
        ft.update(m[a[i]], -a[i]);
        cur -= ft.rsq(m[a[i]], n);
        cur -= a[i] * ft2.rsq(m[a[i]]);
        ft2.update(m[a[i]], -1);
        cur = mod(cur, MOD);
        m[a[i]]--;

        ans += cur;
        ans %= MOD;
        // cout << "cur: " << cur << endl;

    }
    
    return ans;
}

int main(){
    vector<int> a = {4, 3, 2, 1};
    cout << sortedSum(a) << endl;
}