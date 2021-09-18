// UVA 01203 Argus
// Relatively basic priority queue based question. The CRUX of which is declaring a priority queue of the desired type (tuples) sorted in ascending order
// Time: O(k log(n)) where n is the number of registeres, k is the number of queries
// Memory: O(n)

#include <bits/stdc++.h>
using namespace std;

int q_num, k, period;
string op;

priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>> > pq;

int main(){

    while (true)
    {
        cin >> op;
        if (op == "#")
            break;
        cin >> q_num >> period;

        pq.push(make_tuple(period, q_num, period));
    }
    cin >> k;

    for (int i = 0; i < k; i++)
    {
        auto cur = pq.top();
        cout << get<1>(cur) << endl;

        pq.pop();
        //cout << get<0>(cur) + get<2>(cur) << " , " <<  get<1>(cur) << " , " << get<2>(cur) << endl;
        pq.push(make_tuple(get<0>(cur) + get<2>(cur), get<1>(cur), get<2>(cur)));
    }

    return 0;
}