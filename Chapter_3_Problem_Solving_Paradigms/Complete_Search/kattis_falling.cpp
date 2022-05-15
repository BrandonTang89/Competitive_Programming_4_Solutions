/* Kattis - Falling
Abridged problem statement:
    given 0 < d <= 200000 find a, b (a > b >= 0) such that d = a^2 - b^2
    output impossible if no such a, b exists

Observation 1:
    since b >= 0, 
        a^2 - d >= 0
        a >= sqrt(d) giving us a lowerbound on a
    
Observation 2:
    Since a > b, max b = a-1
        a^2 - (a-1)^2 <= d
        [for any a that does not fufil this requirement, even the largest b will not be large enough]

    a <= (d+1)/2  giving us a upperbound on a

Observation 3:
    for each value of a, we use [d = a^2 - b^2] to check if b is an integer

Time: O(sqrt(d)). Mem: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

bool perfect_square(long long n){
    if (ceil((double) sqrt(n)) == floor((double) sqrt(n)))
        return true;
    
    return false;

}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long d, a, b; // a^2 - b^2 = d
    cin >> d;
    for (a=(long long)sqrt(d); a<=(int)(d+1/2);a++){
        
        if (perfect_square(a*a - d)){
            b = (long long) sqrt(a*a - d);
            cout << b << " " << a << endl;
            return 0;
        } 
    }

    cout << "impossible" << endl;

    return 0;
}