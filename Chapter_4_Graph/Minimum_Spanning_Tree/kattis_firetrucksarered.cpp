/**Kattis - firetrucksarered
 * We use a heavily modified Kruskal's algorithm. We maintain a hashtable of (number, node with that
 * number). For each node, we loop through all the numbers that are related to it. If we have
 * encountered that number before, we just join the new node to value of the hashtable at that
 * number. Otherwise, we create a new entry in the hashtable. This creates "star shaped" subgraphs
 * about the node with a specific number, connecting it to other nodes with that number.
 *
 * Time: O(sum mi), Space: O(sum mi)
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

int n, s, u, v, w;
map<int, int> connections;
vector<tuple<int, int, int>> mst_el;

int main() {
    cin >> n;
    mst_el.clear();
    UnionFind uf(n);
    for (int i = 0; i < n; i++) {
        cin >> s;
        for (int j = 0; j < s; j++) {
            int x;
            cin >> x;
            if (connections.find(x) == connections.end()) {
                connections[x] = i;
            } else {
                v = connections[x];
                if (!uf.isSameSet(i, v)) {
                    mst_el.emplace_back(x, i, v);
                    uf.unionSet(i, v);
                }
            }
        }
    }
    if (uf.numDisjointSets() == 1) {
        for (auto &[w, u, v] : mst_el) {
            cout << u + 1 << " " << v + 1 << " " << w << endl;
        }
    } else {
        cout << "impossible" << endl;
    }
}