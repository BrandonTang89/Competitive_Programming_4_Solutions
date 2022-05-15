/* Kattis - nine 

Observation 1:
    The number of such digits is just 8*9*9*9..*9 = 8*(9**(d-1))

Design 1:
    As d might be large and the output might be large , we use fast exponentiation with modulus to ensure efficiency and correctness

Time: (t log d), Mem: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

long long t, d;
const long long mod = 1000000007;

long long fexp(long long b, long long p, long long mod){
    if (p == 0)return 1;
    if (p == 1)return b;

    if (p & 1){
        return (((fexp(b, p>>1, mod)*fexp(b, p>>1, mod))%mod)*b)%mod;
    }
    else{
        return (fexp(b, p>>1, mod)*fexp(b, p>>1, mod))%mod;
    }
    
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t;
    for (int tc=0;tc<t;tc++){
        cin >> d;
        cout << (8*fexp(9, d-1, mod))%mod << endl;
    }

    return 0;
}
