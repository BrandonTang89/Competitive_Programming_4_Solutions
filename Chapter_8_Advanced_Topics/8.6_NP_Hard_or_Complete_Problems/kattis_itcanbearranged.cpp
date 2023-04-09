/**Kattis - itcanbearranged
 * Minimum Path Cover on a DAG. Quite similar to many other questions, we create a graph where the
 * nodes are the class rooms required for a course (the number of which is equal to the number of
 * students divided by the maximum number of students per class room for each course). We then add
 * an edge u -> v if the same physical classroom can be used for both u and v and do a minimum path
 * cover using MCBM.
 *
 * Time: O((n * s/m)^3), Space: O((n * s/m)^2) // loose bound... still can AC and not TLE
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m;
vector<tuple<ll, ll>> times;
vector<int> num_rooms, first_room;
int total_rooms;
vector<vector<int>> cleaning_times, adjlist;
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
    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cin >> n >> m;
        first_room.assign(n, 0);
        times.assign(n, make_tuple(0, 0));
        num_rooms.assign(n, 0);
        total_rooms = 0;
        for (int i = 0; i < n; i++) {
            ll s, e;
            int num_students;
            cin >> s >> e >> num_students;
            num_rooms[i] = (num_students - 1) / m + 1;  // ceil(num_students / m)
            times[i] = make_tuple(s, e);
            first_room[i] = total_rooms;
            total_rooms += num_rooms[i];
        }

        adjlist.assign(total_rooms * 2, vector<int>());
        cleaning_times.assign(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> cleaning_times[i][j];

                if (i == j) continue;

                auto [s1, e1] = times[i];
                auto [s2, e2] = times[j];

                if (e1 + cleaning_times[i][j] >= s2) {
                    continue;  // cannot clean room i before room j
                }

                for (int k = 0; k < num_rooms[i]; k++) {
                    for (int l = 0; l < num_rooms[j]; l++) {
                        adjlist[first_room[i] + k].push_back(total_rooms + first_room[j] + l);
                        adjlist[total_rooms + first_room[j] + l].push_back(first_room[i] + k);
                    }
                }
            }
        }

        int MCBM = cal_MCBM(total_rooms, total_rooms);
        cout << "Case " << t << ": " << total_rooms - MCBM << endl;
    }

    return 0;
}