/**Kattis - eastereggs
 * BSTA + Maximum Independent Set on a Bipartite Graph. For a given minimum distance between a blue
 * and a red egg, we can make a graph where there is an edge between a blue and a red bush if we
 * cannot put an egg in both of them, i.e. their distance is less than the minimum distance. Then,
 * we can find the maximum independent set of this graph to find the maximum number of eggs we can
 * put. If this number is less than n, then we need to increase the minimum distance. Note that the
 * graph is bipartite since the edges are always between blue and red bushes so we can solve this in
 * polynomial time by using MIS = V - MCBM.
 * 
 * Time: O(500 * br + k (<= b + r) * br), Mem: O(br)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, b, r;
vector<vector<int>> adjlist;
vector<tuple<double, double>> blues, reds;
vector<int> match, visited;
int aug(int L)
{
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
int cal_MCBM(int Vleft, int Vright)
{
    match.assign(Vleft + Vright, -1);
    unordered_set<int> freeV;
    for (int L = 0; L < Vleft; L++) freeV.emplace(L);
    int MCBM = 0;

    for (int L = 0; L < Vleft; L++) {  // all left vectices
        vector<int> candidates;
        for (auto R : adjlist[L]) {  // all right vectices neighbouring u
            if (match[R] == -1) {    // if v is unassigned
                candidates.push_back(R);
            }
        }
        if ((int)candidates.size() > 0) {
            MCBM++;
            freeV.erase(L);
            int a = rand() % candidates.size();
            match[candidates[a]] = L;
            match[L] = candidates[a];
        }
    }

    // MCBM Calculation
    for (auto &L : freeV) {
        visited.assign(Vleft, 0);
        MCBM += aug(L);
    }

    return MCBM;
}
int main()
{
    cin >> n >> b >> r;
    for (int i = 0; i < b; i++) {
        double x, y;
        cin >> x >> y;
        blues.push_back(make_tuple(x, y));
    }
    for (int i = 0; i < r; i++) {
        double x, y;
        cin >> x >> y;
        reds.push_back(make_tuple(x, y));
    }

    double lo = 0, hi = 3 * 1e8;
    for (int i = 0; i < 500; i++) {
        double mid = (lo + hi) / 2;

        adjlist.assign(b + r, vector<int>());
        for (int j = 0; j < b; j++) {
            for (int k = 0; k < r; k++) {
                double dist = sqrt(pow(get<0>(blues[j]) - get<0>(reds[k]), 2) +
                                   pow(get<1>(blues[j]) - get<1>(reds[k]), 2));
                if (dist <= mid) {
                    adjlist[j].push_back(k + b);
                    adjlist[k + b].push_back(j);
                }
            }
        }

        int mis = b + r - cal_MCBM(b, r);
        if (mis < n) {  // we need to put the eggs closer
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
    cout << fixed << setprecision(10) << lo << endl;

    return 0;
}