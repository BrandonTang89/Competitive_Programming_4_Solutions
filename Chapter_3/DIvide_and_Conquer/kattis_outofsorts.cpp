/* Kattis - outofsorts

This questions is pretty direct and is just testing our ability to implement bug-free binary search code. Which
might actually not be that easy...

Time: O(n log n), Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

long long n, m, a, c, x0;
long long arr[(long long)1e6 + 9];

bool cus_bs(long long val){ // custom binary search
    int h=n-1, l=0,m;

    while (l<=h){
        m = (l+h)/2;
        if (arr[m] == val)return true;
        if (arr[m] < val){
            l = m+1;
        }
        else{
            h = m-1;
        }
    }
    return false;
}
int main(){
    cin >> n >> m >> a >> c >> x0;
    arr[0] = (a * x0 + c) % m;
    for(int i=1; i<n;i++){
        arr[i] = (a * arr[i-1] + c) % m;
    }

    int counter=0;
    for (int i=0;i<n;i++){
        if (cus_bs(arr[i])){
            counter++;
        }
    }

    cout << counter << endl;
}