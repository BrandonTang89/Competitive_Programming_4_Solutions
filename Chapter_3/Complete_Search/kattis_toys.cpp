/* Kattis - Toys

A standard josephus problem question.

if n == 1, obviously the last toy is the one picked
after killing the nth toy, we start at the next toy at at position k and have only n-1 toys left

Time: O(n), Mem: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

int jos(int n, int k){ // the last toy with n toys and killing every kth toy
    if (n == 1)return 0;
    return ((jos(n-1, k) + k) % n);
}
int main(){
    int n, k;
    cin >> n >> k;

    cout << jos(n,k) << endl;
    return 0;
}