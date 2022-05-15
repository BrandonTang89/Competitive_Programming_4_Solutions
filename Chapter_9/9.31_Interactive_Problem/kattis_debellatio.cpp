/**Kattis - debellatio
 * Interactive problem based on Maximal Cardinality Matching on a general graph.
 * The interactive and general graph version of Kattis - linije. The main ideas is as such:
 * first generate the MCM of the graph.
 *
 * if it is perfect: they start, always pick the node matched to whatever they picked,
 * they will eventually run out of nodes
 *
 * if it is not perfect: we start, pick an umatched node, they will have to pick a matched
 * node, else we have just found an unmatched (but matchable pair). Then we pick the node
 * matched to that. We continue through a series of matched nodes. They will never be
 * able to pick an unmatched node after this because if so, we will just have found an
 * augmenting path, which violates Berges' theorem. Since the graph is finite, they will
 * eventually run out of matched nodes to go to!
 * 
 * The only difficult part is the actual Edmond's matching algorithm, which we use a modifed
 * library implementation for.
 *
 * Time: O(V^3), Space: O(V^2)
 */
#include <bits/stdc++.h>
using namespace std;
const int M = 100; // MAX V
struct struct_edge {
    int v;
    struct_edge* n;
};
typedef struct_edge* edge;

class edmonds_matching {
   private:
    struct_edge pool[M * M * 2];
    edge top = pool, adj[M];
    int V, E, qh, qt, q[M], father[M], base[M];
    bool inq[M], inb[M], ed[M][M];

    int LCA(int root, int u, int v) {
        static bool inp[M];
        memset(inp, 0, sizeof(inp));
        while (1) {
            inp[u = base[u]] = true;
            if (u == root) break;
            u = father[match[u]];
        }
        while (1) {
            if (inp[v = base[v]])
                return v;
            else
                v = father[match[v]];
        }
    }
    void mark_blossom(int lca, int u) {
        while (base[u] != lca) {
            int v = match[u];
            inb[base[u]] = inb[base[v]] = true;
            u = father[v];
            if (base[u] != lca) father[u] = v;
        }
    }
    void blossom_contraction(int s, int u, int v) {
        int lca = LCA(s, u, v);
        memset(inb, 0, sizeof(inb));
        mark_blossom(lca, u);
        mark_blossom(lca, v);
        if (base[u] != lca) father[u] = v;
        if (base[v] != lca) father[v] = u;
        for (int u = 0; u < V; u++)
            if (inb[base[u]]) {
                base[u] = lca;
                if (!inq[u]) inq[q[++qt] = u] = true;
            }
    }
    int find_augmenting_path(int s) {
        memset(inq, 0, sizeof(inq));
        memset(father, -1, sizeof(father));
        for (int i = 0; i < V; i++) base[i] = i;
        inq[q[qh = qt = 0] = s] = true;
        while (qh <= qt) {
            int u = q[qh++];
            for (edge e = adj[u]; e; e = e->n) {
                int v = e->v;
                if (base[u] != base[v] && match[u] != v) {
                    if ((v == s) || (match[v] != -1 && father[match[v]] != -1))
                        blossom_contraction(s, u, v);
                    else if (father[v] == -1) {
                        father[v] = u;
                        if (match[v] == -1)
                            return v;
                        else if (!inq[match[v]])
                            inq[q[++qt] = match[v]] = true;
                    }
                }
            }
        }
        return -1;
    }
    int augment_path(int s, int t) {
        int u = t, v, w;
        while (u != -1) {
            v = father[u];
            w = match[v];
            match[v] = u;
            match[u] = v;
            u = w;
        }
        return t != -1;
    }

   public:
    int match[M];  // matches
    edmonds_matching(int initV, int initE) : V(initV), E(initE) { memset(ed, 0, sizeof(ed)); }

    void add_edge(int u, int v) {
        if (ed[u][v]) return;
        ed[u][v] = ed[v][u] = true;
        top->v = v, top->n = adj[u], adj[u] = top++;
        top->v = u, top->n = adj[v], adj[v] = top++;
    }
    int edmonds() {
        int matchc = 0;
        memset(match, -1, sizeof(match));  // unmatched is -1
        for (int u = 0; u < V; u++)
            if (match[u] == -1) matchc += augment_path(u, find_augmenting_path(u));
        return matchc;
    }
};
int main() {
    int u, v;
    int V, E;
    cin >> V >> E;
    edmonds_matching em(V, E);
    while (E--) {
        cin >> u >> v;
        u--;
        v--;
        em.add_edge(u, v);
    }
    int num_matches = em.edmonds();
    if (num_matches * 2 == V) {
        // Perfect matching, they start
        cout << 2 << endl << flush;
    } else {
        cout << 1 << endl << flush;
        for (int i = 0; i < V; i++) {
            if (em.match[i] == -1) {
                cout << i + 1 << endl << flush;
                break;
            }
        }
    }

    while (true) {
        int cur;
        cin >> cur;
        if (cur == 0) break;

        cur--;
        assert(em.match[cur] != -1);
        cout << em.match[cur] + 1 << endl << flush;
    }
}