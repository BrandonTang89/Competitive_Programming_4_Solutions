/**Kattis - downfall
 * A variation of UFDS. The idea is essentially to implement the buckets as nodes in a tree that
 * lead up to a parent node which is the next bucket that is not yet full. We use the path compression
 * heuristic to compress paths and keep the trees as flat as possible.
 * 
 * Time: O(n + r), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

class Buckets {
   public:
    vi p, rank, bucketCap;  // vi p is the key part
    int numSets;

    Buckets(int N, int K)
    {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i) p[i] = i;
        rank.assign(N, 0);       // optional speedup
        bucketCap.assign(N, K);  // optional feature
        numSets = N;             // optional feature
        bucketCap[0] = 1e9;
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }

    int add_drop(int i)
    {
        int x = findSet(i);
        bucketCap[x]--;
        if (bucketCap[x] == 0) {
            p[x] = x - 1;
        }
        return x;
    }
};

int main()
{
    ll n, r, k, a, b, x0;
    cin >> n >> r >> k >> x0 >> a >> b;
    ll ans = 0;
    Buckets bu(n + 1, k);
    for (int i = 1; i <= r; ++i) {
        ll x = (a * x0 + b) % n;
        ll bucketflowed = bu.add_drop(x + 1);
        ans = (53 * ans + bucketflowed - 1) % 199933;
        x0 = x;
    }
    if (bu.bucketCap[0] != 1e9) {
        cout << "OVERFLOW\n";
    }
    else {
        cout << ans << "\n";
    }

    return 0;
}