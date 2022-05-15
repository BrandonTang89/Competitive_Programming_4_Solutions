/* Kattis - crackingrsa
This is probably the most basic of rsa type questions.

Observation 1:
    Since n is small enough, we don't need any funny or super smart factorisation algorithm :)
    brute force suffices

Observation 2:
    by bezout's identity, since e and phi are coprime, there exist a, b such that a*e + b*phi = 1
    Taking mod on both sides, a*e = 1 mod phi, not that there a = d, ie we are trying to compute
    the modulo inverse, we can use the extended euclidean algorithm or...
    
    just brute force since the numbers are small!

Time: O(tc * n), Mem: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

long long t, m, n, e, p, q, d, phi;
int main(){
    cin >> t;
    for (int tc=0;tc<t;tc++){
        cin >> n >> e;
        
        // factorise n;
        for (p=2; p<1000; p++){
            for (q=2; q<1000; q++){
                if (p*q == n)break;
            }
            if (p*q == n)break;
        }


        phi = (p-1)*(q-1);
        //cout << "PHI: " << phi << endl;

        for (d = 2; d < phi; d++){
            if ((d*e) % phi == 1){
                cout << d << endl;
                break;
            }
        }

        //cout << "hello";

    }

    
}