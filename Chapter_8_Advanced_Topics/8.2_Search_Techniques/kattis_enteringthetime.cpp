/**Kattis - enteringthetime
 * Quite an obvious though potentially slightly tedious problem. We just do 2 separate BFSs, 1 for
 * the hours and 1 for the minutes, then our solution is just following the shortest paths along
 * both of the BFSs.
 * 
 * Time: O(1), Mem: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

vector<int> hour_dist, min_dist;
vector<int> hour_parent, min_parent;
queue<int> q;

int main()
{
    int src_h, src_m, dest_h, dest_m;
    char dummy;
    cin >> src_h >> dummy >> src_m >> dest_h >> dummy >> dest_m;

    hour_dist.assign(24, 1e9);
    min_dist.assign(60, 1e9);
    hour_parent.assign(24, -1);
    min_parent.assign(60, -1);

    q.push(src_h);
    hour_dist[src_h] = 0;
    while (!q.empty()) {
        int x = q.front();
        if (x == dest_h) break;
        q.pop();
        int tens = x / 10;
        int ones = x % 10;
        vector<int> next = {((ones + 1) % 10) + tens * 10, ((ones + 9) % 10) + tens * 10,
                            ((tens + 1) % 10) * 10 + ones, ((tens + 9) % 10) * 10 + ones};

        for (int y : next) {
            if (0 <= y && y < 24) {
                if (hour_dist[y] > hour_dist[x] + 1) {
                    hour_dist[y] = hour_dist[x] + 1;
                    hour_parent[y] = x;
                    q.push(y);
                }
            }
        }
    }
    while (!q.empty()) q.pop();

    q.push(src_m);
    min_dist[src_m] = 0;
    while (!q.empty()) {
        int x = q.front();
        if (x == dest_m) break;
        q.pop();
        int tens = x / 10;
        int ones = x % 10;
        vector<int> next = {((ones + 1) % 10) + tens * 10, ((ones + 9) % 10) + tens * 10,
                            ((tens + 1) % 10) * 10 + ones, ((tens + 9) % 10) * 10 + ones};

        for (int y : next) {
            if (0 <= y && y < 60) {
                if (min_dist[y] > min_dist[x] + 1) {
                    min_dist[y] = min_dist[x] + 1;
                    min_parent[y] = x;
                    q.push(y);
                }
            }
        }
    }

    cout << hour_dist[dest_h] + min_dist[dest_m] + 1 << endl;
    vector<int> hours;
    vector<int> mins;
    int curr = dest_h;
    while (curr != -1) {
        hours.push_back(curr);
        curr = hour_parent[curr];
    }
    for (int i = hours.size() - 1; i >= 0; i--) {
        printf("%02d:%02d\n", hours[i], src_m);
    }
    curr = dest_m;
    while (curr != -1) {
        mins.push_back(curr);
        curr = min_parent[curr];
    }
    for (int i = mins.size() - 2; i >= 0; i--) {
        printf("%02d:%02d\n", dest_h, mins[i]);
    }

    return 0;
}