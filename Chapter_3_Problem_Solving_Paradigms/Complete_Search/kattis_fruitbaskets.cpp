/* Kattis - fruitbasket

Observation 1:
    First we note that the are much less subsets less than 200g than >= 200g. We know this for sure because the weight of
    each fruit is at least 50g, meaning that for all subsets less than 200g, there are at most 4 fruits. Conversely,
    if we tried to find baskets at least 200g, it would be baskets with more than 4 fruits++. WIth 40 fruits, its obvious
    that finding the complement is more efficient.

Design 1:
    This is something i should probably have done in my previous backtracking questions... pass a position variable
    c that denotes that current element being considered. this way we dont need to maintain some sort of state array for
    the function to know which position we are on. Not only reduces code complexity but also reduces memory use and
    improves the time efficiency

Debugging 1:
    for doing (1<<x) for large values of x (32<x<64), use 1LL or 1ULL for long long or unsigned long long.

Time: O ((nC4) + (nC3) + (nC2) + (nC1)) since we only visit states with 4 or less fruits, where nC4 is n choose 4
Mem: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

int n; 
long long weights[40];
long long total_basket_weights=0;
void backtrack(int c, long long bw){ //currently considered position, basket weight
    if (c == n){
        total_basket_weights += bw;
        return;
    }

    if (weights[c] + bw < 200){ // if possible, include fruit c as well
        backtrack(c+1, bw+weights[c]);
    }

    backtrack(c+1, bw);
}
int main(){
    cin >> n;
    long long total = 0;
    for (int i=0;i<n;i++){
        cin >> weights[i];
        total += weights[i];
    }

    total = total * ((1LL)<<(n-1)); // each weight is counted in half the baskets

    backtrack(0, 0);

    cout << total - total_basket_weights << endl;

    return 0;
}