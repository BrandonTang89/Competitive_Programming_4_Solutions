/**Kattis - undetected
 * Complete search + geometry + UFDS. It's kinda like an easier version of kattis - passingthrough.
 * The logic is that we initially set up a UFDS with all the circles separate, then we join circles
 * if they are connected directly or indirectly by merging sets. Then we check if any left and right
 * circle are connected somehow. 
 * 
 * Time: O(n^3), Space: O(n)
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

class UnionFind {  // OOP style
   private:
    vi p, rank, setSize;  // vi p is the key part
    int numSets;

   public:
    UnionFind(int N) {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i) p[i] = i;
        rank.assign(N, 0);     // optional speedup
        setSize.assign(N, 1);  // optional feature
        numSets = N;           // optional feature
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    int numDisjointSets() { return numSets; }             // optional
    int sizeOfSet(int i) { return setSize[findSet(i)]; }  // optional

    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;         // i and j are in same set
        int x = findSet(i), y = findSet(j);  // find both rep items
        if (rank[x] > rank[y]) swap(x, y);   // keep x 'shorter' than y
        p[x] = y;                            // set x under y
        if (rank[x] == rank[y]) ++rank[y];   // optional speedup
        setSize[y] += setSize[x];            // combine set sizes at y
        --numSets;                           // a union reduces numSets
    }
};

int n;
vector<tuple<int, int, int>> circles;  // x, y, r
vector<int> on_left, on_right;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y, r;
        cin >> x >> y >> r;
        circles.emplace_back(x, y, r);

        if (x - r <= 0) on_left.emplace_back(i);
        if (x + r >= 200) on_right.emplace_back(i);
    }

    UnionFind uf(n);

    for (int i = 0; i < n; i++) {
        // turn on i
        auto [x, y, r] = circles[i];
        for (int j = 0; j < i; j++) {
            auto [x2, y2, r2] = circles[j];
            if (sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2)) <= r + r2) {
                uf.unionSet(i, j);
            }
        }

        for (auto l : on_left) {
            for (auto r : on_right) {
                if (uf.isSameSet(l, r)) {
                    cout << i << endl;
                    return 0;
                }
            }
        }
    }

    return 0;
}