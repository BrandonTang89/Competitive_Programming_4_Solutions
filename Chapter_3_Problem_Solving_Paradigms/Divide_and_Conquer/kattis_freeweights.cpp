/* Kattis - freeweights

Observation 1:
    Given a max weight we can carry, we can just put all weights <= max weight in sorted order at the front of the 
    first row. The remaining weights can only be rolled about... Thus when we check, we can just ignore all the 
    weights <= max weight and start pairing the weights we cannot carry. if at any point of time, 2 weights of a heavy
    pair are not adjacent, we know that we need a higher weight.

    Given this, just BSTA making sure to try carrying no weights

Time: O(n log n), Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

int n;
int r1[(int)1e6 + 9], r2[(int)1e6 + 9];
set<int>s;
vector<int> sorted_weights;

int previous;
bool check(int w){
    bool valid = true;
    previous = -1;
    for (int i=0;i<n;i++){
        if (r1[i] <= w)continue; // ignore if less than or equal to weight
        if (previous != -1){
            if (r1[i] == previous){
                previous = -1;
                continue;
            }
            else{
                valid = false;
                break;
            }
        }
        previous = r1[i];
    }
    if (previous != -1) valid = false;
    previous = -1;
    for (int i=0;i<n;i++){
        if (r2[i] <= w)continue; // ignore if less than or equal to weight
        if (previous != -1){
            if (r2[i] == previous){
                previous = -1;
                continue;
            }
            else{
                valid = false;
                break;
            }
        }
        previous = r2[i];
    }

    return valid;
}
int main(){
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> r1[i];
        s.insert(r1[i]);
    }
    for (int i=0;i<n;i++){
        cin >> r2[i];
        s.insert(r2[i]);
    }
    
    s.insert(0);
    for (auto w: s){
        sorted_weights.emplace_back(w);
    }

    // BSTA
    int h=n, l=0, m, w;
    while (l + 1 < h){
        m = (l+h)/2;
        //printf("l: %d, m: %d, h:%d\n", l, m, h);
        
        w = sorted_weights[m];
        if (check(w)){ // can do with this weight so we should check lower weights
            h = m;
        }
        else{ // cant do with this weight
            l = m+1;
        }
    }
    if (check(sorted_weights[l])){
        cout << sorted_weights[l] << endl;
    }
    else
        cout << sorted_weights[h] << endl;

    return 0;
}