/* Kattis - Snapperhard

Observation 1:
    A simple analysis shows that the process is equivalent to counting in binary. The n snappers are analagous to n bits and the final light is on
    when all the n bits are turned on. Thus the light will turn on if k == 2**n -1 and be off for all k < 2**n -1

Observation 1.1:
    If k > 2**n, notice that on the 2**n snap, all the snappers are initialy on and powered, thus the snap resets the snapers to the initial conditions
    thus we can generalise that the light will be on iff k % 2**n == 2**n -1 for all k

Design 1:
    We can use bit manipulation to speed up the power and modulo operations, (k % 2**n == 2**n -1) --> ((k & ((1<<n)-1)) == (1<<n)-1)

Time: O(T), Mem: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

long long T, n, k;
int main(){
    cin >> T;
    for (int tc=1;tc<=T;tc++){
        cin >> n >> k;
        if ((k & ((1<<n)-1)) == (1<<n)-1){
            printf("Case #%d: ON\n", tc);
        }
        else{
            printf("Case #%d: OFF\n", tc);
        }
    }


    
}
