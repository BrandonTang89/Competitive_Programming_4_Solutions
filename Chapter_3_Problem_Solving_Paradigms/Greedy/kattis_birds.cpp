/* Kattis - Birds
Observation 1:
    Given 2 birds at u and l and no other birds in between, we can fit in (l-u)/d - 1 new birds... This comes from greedily
    putting each new bird as near (d distance) to the previous bird as possible. Thus we should sort the existing birds
    and then process them linearly.

Observation 2:
    the most tricky part of this is actually the ends. But, we just need to know that the first bird can only be at 6 and
    further, so we just create a dummy bird at 6-d which will ensure the first bird placed will be at most at 6. A similar
    thought process results in us finding out that placing a dummy bird at l-6+d results in the correct answer for the end
    as well.
    
Time: O(n log n), Mem: O(n)
*/ 
#include <bits/stdc++.h>
using namespace std;

int l, d, n, pos;
vector<int>birds;
int main(){
    cin >> l >> d >> n;
    for (int i=0;i<n;i++){
        cin >> pos;
        birds.emplace_back(pos);
    }
    birds.emplace_back(6-d);
    birds.emplace_back((l-6+d));

    sort(birds.begin(), birds.end());

    //for (auto i: birds){cout << i << " ";}cout << endl;

    int counter=0;
    for(int i=0;i<birds.size()-1;i++){
        counter = counter + (birds[i+1]-birds[i])/d - 1;
    }

    cout << counter << endl;

    return 0;
}