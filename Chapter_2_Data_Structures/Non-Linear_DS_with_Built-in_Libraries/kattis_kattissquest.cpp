/*
Kattis - Kattissquest
simplish problem that can be solved with a map of priority queues

Debugging 1:
    make sure the map is never empty... do so by putting a dummy element at INT_MAX index

Time complexity is as such because in the worst case scnerio, all the adds come before the queries. with at most O(n) adds, we can only remove up to that amount
of quests despite having O(n) queries, each potentially getting the entire data structure worth of quests. As each poster takes at most O(log n) time to remove.
the overall time is O(n log n)
Time: O(n log n), Mem: O(n)
*/ 
#include <bits/stdc++.h>
using namespace std;

long long n, e, g, x;
string op;
map<long long, priority_queue<long long>> m; // m[energy] = pq: {reward0, reward1, ...}
int main(){
    cin >> n;
    m[INT_MAX].push(0);
    for (int q=0;q<n;q++){
        cin >> op;
        if (op == "add"){
            cin >> e >> g;
            //printf("pushing e,g : %d,%d\n", e,g);
            m[e].push(g);
        }
        else if (op == "query"){
            cin >> x;
            g=0;
            while(true){
                //printf("x:%d\n",x);
                auto it = m.lower_bound(x);
                if (it->first > x)it--;
                if (x < m.begin()->first){
                    //cout << "x broke at "<< x << endl;
                    //cout << "m begin first " << m.begin()->first << endl;
                    //cout << "it = m.begin() " << (it == m.begin()) << endl;
                    break;
                }
                
                x -= it->first;
                g += it->second.top();
                m[it->first].pop();
                
                if (it->second.size() == 0){
                    // << " meow" << endl;
                    m.erase(it);
                }

            }
            cout << g << endl;
            
        }
    }
    return 0;
}
