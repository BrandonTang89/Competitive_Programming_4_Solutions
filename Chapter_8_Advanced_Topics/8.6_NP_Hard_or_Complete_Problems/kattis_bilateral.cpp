/**Kattis - bilateral
 * An annoying and long problem. The main part is MVC on a bipartite graph. However, we need to print the solution.
 * And not just any solution! We need to put person 1009 in the solution if there is a MVC with it. We observe from
 * Koing's Theorem that if we want 1009 to be in the solution if possible then we should include it in the MCBM 
 * (since 1009 will be on the left). So how do we ensure this? We analyse the augmenting path algorithm and see that
 * if 1009 is the first vertex to be processed, it will be greedily matched if possible. Following which, all calls
 * to aug will never unmatch 1009. Thus we need to relabel the vertices properly such that 1009 is vertex 0 if it exists.
 * 
 * The rest of the problem is just slowly writing the code for MCBM and calculating the MVC via Koing's Theorem.
 * 
 * Time: O(VE), Space: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int e, n, nL = 0;
set<int> nodes;
map<int, int> m, m_reverse;
vector<int> adjlist[2000];
vector<pair<int, int>> edges;
vector<int> match, visited;
// MCBM Augmenting Path Algorithm
int aug(int L) {
    if (visited[L]) return 0;
    visited[L] = 1;
    for (auto &R : adjlist[L]) {
        if (match[R] == -1 || aug(match[R])) {
            match[R] = L;
            match[L] = R;
            return 1;
        }
    }
    return 0;
}

set<int> U;  // U is the unmatched vertices in the left set
set<int> Z;  // is the vertices in U or connected to U via an augmenting path
set<int> mvc;
bool connected_to_u(int i) {
    if (visited[i]) return false;
    visited[i] = true;

    if (U.count(i)) return true;
    if (i < nL) {  // left side
        return connected_to_u(match[i]);
    }
    for (auto &j : adjlist[i]) {  // right side
        if (match[i] == j) continue;
        if (connected_to_u(j)) return true;
    }
    return false;
}
int main() {
    n = 0;
    cin >> e;

    int u, v;
    for (int i = 0; i < e; i++) {
        cin >> u >> v;
        edges.push_back(make_pair(u, v));
        if (nodes.find(u) == nodes.end()) {
            nodes.insert(u);
            nL++;
            n++;
        }
        if (nodes.find(v) == nodes.end()) {
            nodes.insert(v);
            n++;
        }
    }
    int counter = 0;
    if (nodes.find(1009) != nodes.end()) { // ensure 1009 is vertex 0
        m[1009] = 0;
        m_reverse[0] = 1009;
        nodes.erase(1009);
        counter = 1;
    }
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        m[*it] = counter;
        m_reverse[counter] = *it;
        counter++;
    }
    for (auto &[u, v] : edges) {
        u = m[u];  // convert to our own naming
        v = m[v];
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }

    match.assign(n, -1);
    int MCBM = 0;
    for (int u = 0; u < nL; u++) {    // all left vectices
        for (auto &v : adjlist[u]) {  // all right vectices neighbouring u
            if (match[v] == -1) {     // if v is unassigned
                match[v] = u;         // match v to u
                match[u] = v;         // match u to v
                MCBM++;
                break;
            }
        }
    }

    // MCBM Calculation
    for (int L = 1; L < nL; L++) { // vertex 0 already matched if possible
        if (match[L] == -1) {
            visited.assign(n, 0);
            MCBM += aug(L);
        }
    }
    cout << MCBM << endl;

    for (int i = 0; i < nL; i++) {
        if (match[i] == -1) {
            U.insert(i);
        }
    }

    for (int i = 0; i < n; i++) {
        visited.assign(n, 0);
        if (connected_to_u(i)) {
            Z.insert(i);
        }
    }

    // MVC = (L \ Z) union (R intersect Z)
    for (int i = 0; i < nL; i++) {
        if (Z.count(i) == 0) {
            mvc.insert(i);
        }
    }
    for (int i = nL; i < n; i++) {
        if (Z.count(i)) {
            mvc.insert(i);
        }
    }

    for (auto i : mvc) {
        cout << m_reverse[i] << endl;
    }

    return 0;
}