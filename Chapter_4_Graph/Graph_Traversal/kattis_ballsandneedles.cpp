/**Kattis - ballsandneedles
 * Relatively straightforward graph modelling + non-trivial cycle check. Most of the time is just
 * spent maping the tuples to indices and crafting 2x adjacency list for the true balls and the
 * shadow balls. Then, we just use standard library code to check for cycles.
 *
 * Time: O(n log n + e), Space: O(n + e)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int e, n = 0;
int nf = 0;
map<tuple<int, int, int>, int> m1;
map<tuple<int, int>, int> m2;

vector<vector<int>> adjlist1, adjlist2;

enum { UNVISITED = -1, EXPLORED = -2, VISITED = -3 };  // three flags
vi dfs_num;
vi dfs_parent;  // back vs bidirectional

bool has_cycle = false;
void cycleCheck(int u, vector<vector<int>> &AL) {  // check edge properties
    dfs_num[u] = EXPLORED;                         // color u as EXPLORED
    for (auto &v : AL[u]) {                        // C++17 style, w ignored
        if (dfs_num[v] == UNVISITED) {             // EXPLORED->UNVISITED
            dfs_parent[v] = u;                     // a tree edge u->v
            cycleCheck(v, AL);
        } else if (dfs_num[v] == EXPLORED) {   // EXPLORED->EXPLORED
            if (v == dfs_parent[u] || v == u)  // differentiate them
                continue;
            else  // the most frequent application: check if the graph is cyclic
                has_cycle = true;
        }
    }
    dfs_num[u] = VISITED;  // color u as VISITED/DONE
}

int main() {
    cin >> e;
    for (int i = 0; i < e; i++) {
        int ux, uy, uz, vx, vy, vz;
        cin >> ux >> uy >> uz >> vx >> vy >> vz;
        if (m1.count(make_tuple(ux, uy, uz)) == 0) {
            m1[make_tuple(ux, uy, uz)] = n++;
            adjlist1.push_back(vector<int>());
        }
        if (m1.count(make_tuple(vx, vy, vz)) == 0) {
            m1[make_tuple(vx, vy, vz)] = n++;
            adjlist1.push_back(vector<int>());
        }

        adjlist1[m1[make_tuple(ux, uy, uz)]].push_back(m1[make_tuple(vx, vy, vz)]);
        adjlist1[m1[make_tuple(vx, vy, vz)]].push_back(m1[make_tuple(ux, uy, uz)]);

        if (m2.count(make_tuple(ux, uy)) == 0) {
            m2[make_tuple(ux, uy)] = nf++;
            adjlist2.push_back(vector<int>());
        }
        if (m2.count(make_tuple(vx, vy)) == 0) {
            m2[make_tuple(vx, vy)] = nf++;
            adjlist2.push_back(vector<int>());
        }

        adjlist2[m2[make_tuple(ux, uy)]].push_back(m2[make_tuple(vx, vy)]);
        adjlist2[m2[make_tuple(vx, vy)]].push_back(m2[make_tuple(ux, uy)]);
    }

    // Cycle Check adjlist1
    dfs_num.assign(n, UNVISITED);
    dfs_parent.assign(n, -1);
    for (int i = 0; i < n && has_cycle == false; i++) {
        if (dfs_num[i] == UNVISITED) {
            cycleCheck(i, adjlist1);
        }
    }

    if (has_cycle) {
        cout << "True closed chains" << endl;
    } else {
        cout << "No true closed chains" << endl;
    }

    // Cycle Check adjlist2
    has_cycle = false;
    dfs_num.assign(nf, UNVISITED);
    dfs_parent.assign(nf, -1);
    for (int i = 0; i < nf && has_cycle == false; i++) {
        if (dfs_num[i] == UNVISITED) {
            cycleCheck(i, adjlist2);
        }
    }
    if (has_cycle) {
        cout << "Floor closed chains" << endl;
    } else {
        cout << "No floor closed chains" << endl;
    }

    return 0;
}