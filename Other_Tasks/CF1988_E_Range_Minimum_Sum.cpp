#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
vector<ll> a;
class rupq {
 public:
  vector<ll> arr;

  rupq(int n) { arr.resize(n + 1, 0); }

  void update(int l, int r, ll val) {  // inclusive l, r
    arr[l] += val;
    arr[r + 1] -= val;
  }

  vector<ll> get() {
    vector<ll> res;
    ll cur = 0;
    for (int i = 0; i < arr.size() - 1; i++) {
      cur += arr[i];
      res.push_back(cur);
    }
    return res;
  }
};

int main() {
  int tc;
  cin >> tc;
  while (tc--) {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    set<int> s;
    s.insert(-1);
    s.insert(n);
    vector<ll> contribution(n, 0);  // Contribution via being minimum in a subarray
    rupq adjustment(n);             // Contribution via being present but not minimum in a subarray
    vector<ll> extra(n, 0);         // Extra contribution gotten by others if you were not present

    vector<pair<ll, ll>> x;
    for (int i = 0; i < n; i++) {
      x.push_back({a[i], i});
    }
    sort(x.begin(), x.end());

    ll fa = 0;
    for (int i = 0; i < n; i++) {
      // find the left and right bounds
      ll val = x[i].first;
      int idx = x[i].second;
      auto rightit = s.upper_bound(idx);
      auto leftit = rightit;
      leftit--;

      ll right = *rightit;
      ll left = *leftit;

      contribution[idx] = (val * (right - idx) * (idx - left));
      fa += contribution[idx];

      // everything from left+1 to idx-1 will have the adjustment of (val * (right - idx))
      adjustment.update(left + 1, idx - 1, val * (right - idx));

      // everything from idx+1 to right-1 will have the adjustment of (val * (idx - left))
      adjustment.update(idx + 1, right - 1, val * (idx - left));

      if (left != -1) {
        // if left was removed, we would get some extra contribution
        auto lleftit = leftit;
        lleftit--;
        ll lleft = *lleftit;
        extra[left] += ((left - lleft - 1) * (right - idx) * val);
      }

      if (right != n) {
        // if right was removed, we would get some extra contribution
        auto rrightit = rightit;
        rrightit++;
        ll rright = *rrightit;
        extra[right] += ((idx - left) * (rright - right - 1) * val);
      }

      s.insert(idx);
    }

    auto xx = adjustment.get();
    for (int i = 0; i < n; i++) {
      cout << fa - contribution[i] - xx[i] + extra[i] << " ";
    }
    cout << endl;
  }

  return 0;
}