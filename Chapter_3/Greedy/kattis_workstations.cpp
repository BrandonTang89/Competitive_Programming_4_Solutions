/* Kattis - workstations
Observation 1:
    We should greedily select available but not closed workstations that are going to "expire" the soonest. This can
    be kept track of with an ascending priority queue.

    We should also keep track of the computers being used and store them in a priority queue based on the time they end
    so we can efficiency find the computers that have become available after use.

Time: O(n log n)
Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
int a, s;
int unlockings = 0;
priority_queue<int, vector<int>, greater<int>> avail; // assign the station that closes the earliest
priority_queue<int, vector<int>, greater<int>> inuse; // pop stations that have been completed

vector<pair<int,int>> v;
int main(){
    cin >> n >> m;
    for (int i=0;i<n;i++){
        cin >> a >> s;
        v.emplace_back(make_pair(a,s));
    }
    sort(v.begin(),v.end());

    for (auto i:v){
        a = i.first;
        s = i.second;

        while (!inuse.empty()){ // move finished work stations to stack
            if (inuse.top() <= a){
                avail.push(inuse.top() + m);
                inuse.pop();
            }
            else{
                break;
            }
        }

        while (!avail.empty()){//expired stations
            if (avail.top() < a)avail.pop();
            else break;
        }

        if (avail.empty()){
            unlockings++;
        }
        else{
            avail.pop();
        }
        inuse.push(i.first+i.second);
    }

    cout << n - unlockings << endl;

    return 0;
}