/* Kattis - delivery
Observation 1:
    After delivering to a negative position, if the next place to deliver is a positive location, we always need
    to pass the post office, so we would always want to fill up the truck again. Likewise for going to a negative
    position after a positive position...

    So, for any optimal solution, note that we can always divide the solution into segment of 
    0 -> x1 -> x2 -> x3 ... -> 0
    where all values of x are positive or all negative, ie the truck visits one side of the line exclusively
    then goes back to the post office.

    What this means is that we instead of making life hard and considering the 2 sides of the numberline together
    we can split it such that the truck does all the negative values first before the positive values. This is done by taking
    whatever optimal solution and rearranging the segments such that all the negative segments come before
    the positive segments this still results in optimal distance as the truck is always back at 0 before doing each segment

    To make things even easier, we can just convert the negative part into a second positive part that we can solve in the
    same way as the positive side...

Observation 2:
    With the reduced problem of only positive values of x, we note that we would want to ensure we have a full load 
    to travel to the furthest out town to ensure minimum number of trips there. If we have any excess, we can unload it
    at the second furthest house on the way back to the station (and if still have then dump at 3rd furthest, etc).
    Doing this repeatedly results in an optimal strategy.

Time: O(n log n + sum(t))
Mem: O(n)

*/
#include <bits/stdc++.h>
using namespace std;

int n, k, t, x;
vector<pair<int,int>> vpos, vneg;

int sim(vector<pair<int,int>> v){
    int dist = 0;
    int cl = 0;// currently carried letters
    int index = 0;
    while(index < v.size()){
        //printf("visiting %d with %d letters\n", v[index].first, cl);
        if (v[index].second <= cl){ // dump the required letters at the place
            cl -= v[index].second;
            index++;
        }
        else{ // go refill the truck
            v[index].second -= cl;
            cl = k;
            dist += v[index].first * 2;
        }
    }

    //printf("dist: %d\n", dist);
    return dist;
}
int main(){
    cin >> n >> k;
    for (int i=0;i<n;i++){
        cin >> x >> t;
        if (x < 0){
            vneg.emplace_back(make_pair(-x,t));
        }
        else{
            vpos.emplace_back(make_pair(x, t));
        }
    }
    sort(vpos.begin(), vpos.end(), greater<pair<int,int>>());
    sort(vneg.begin(), vneg.end(), greater<pair<int,int>>());

    int total_d = sim(vneg) + sim(vpos);

    cout << total_d << endl;
    
    return 0;
}