/* Kattis - airconditioned
Observation 1:
    This is actually similar to the interval scheduling problem. We first sort the minions by upper limit and then
    note that it is always not worse to put the first room at the temperature of the upper limit of the first minion.
    This is because doing so would allow the first minion to fit while giving the largest range that allows as many
    subsequent minions to fit as possible. Now we have dealt with all the minions with lower limit <= upper limit of
    the first minion, we can repeat the process again, choosing the next room to be the upper limit of the next minion

Time: O(n log n) since sorting is included
Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

int n, l, u;
vector<pair<int,int>> minions; // (upper, lower)
int main(){
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> l >> u;
        minions.emplace_back(make_pair(u,l));
    }
    sort(minions.begin(), minions.end());

    int rt = 0;
    int counter = 0;
    for (auto minion: minions){
        l = minion.second;
        u = minion.first;

        if (rt >= l && rt <= u)continue; // can fit the minion into the room

        counter++;
        rt = u;
    }
    cout << counter << endl;


    return 0;
}