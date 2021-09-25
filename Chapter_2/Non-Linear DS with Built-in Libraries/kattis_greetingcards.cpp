/*
Kattis - Greetingcards

Observation 1:
    querying wolfram alpha "integer solutions to 2018^2 = x^2 + y^2" results in only 12 solutions. Thus for each
    point we process, we can check these 12 neighbours and see if there exist other previously processed points.

    Note that we shouldnt double count the line segments

Time: O(n log n) with bBST/ expected O(n) with hash table
Mem: O (n)

*/ 
#include <bits/stdc++.h>
using namespace std;

int n, x, y;
long long ans;
int dx[12] = {2018, -2018, 0, 0, 1118, 1118, -1680, 1680, 1680, -1680, -1118, -1118};
int dy[12] = {0, 0, 2018, -2018, -1680, 1680, 1118, 1118, -1118, -1118, 1680, -1680};
unordered_set<pair<int,int>> s;
int main(){
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> x >> y;
        int nx, ny;
        for (int j=0;j<12;j++){
            nx = x + dx[j];
            ny = y + dy[j];

            if (s.find(make_pair(nx,ny)) != s.end())ans++;
        }
        s.insert(make_pair(x,y));
    }

    cout << ans << endl;
    return 0;
}