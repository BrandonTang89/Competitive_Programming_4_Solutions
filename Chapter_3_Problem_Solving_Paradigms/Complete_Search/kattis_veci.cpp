/* Kattis - veci
A very simple complete search question. Just try all permutations of the digits.

Debugging:
    Remember to sort the v vector before using next_permutation

Time: O(n) (since 2^ log(n))
Mem: O(log n)
*/
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int>v;
int main(){
    cin >> n;
    for (int c=n; c>0; c/=10){
        v.emplace_back(c%10);
    }
    sort(v.begin(), v.end());

    int min_val = INT_MAX;
    int c=0;
    do{
        c = 0;
        for (int i=0;i<v.size();i++){
            c += pow(10, i)*v[i];
        }
        if (c > n)
            min_val = min(min_val, c);
    }
    while (next_permutation(v.begin(), v.end()));

    if (min_val == INT_MAX){
        cout << 0 << endl;
    }
    else{
        cout << min_val << endl;
    }
}