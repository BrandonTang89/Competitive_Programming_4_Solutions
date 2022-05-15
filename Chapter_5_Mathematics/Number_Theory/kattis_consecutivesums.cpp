/**Kattis - consecutivesums
 * This problem relies mostly on math to solve fast.
 * from the AP sum n = at + t(t-1)/2, where a is the first term and t is the number of terms.
 * we get that 2n = t(2a+t-1), ie for every divisor of n, i, we can try to set t=i,
 * 2a+t-1 = 2n/i. We know that 2a+t-1 must be > t since a >= 1. so we know that i <= sqrt(n)
 * 
 * but how do we know if n/i can be equal to 2a+t-1? well, if a is an integer, it is valid.
 * manipulating n/i = 2a+t-1, we get that a = (n/i-t+1)/2. So we just check if n/i -t + 1 is even.
 * 
 * Since we check in increasing t, we will get the smallest possible t.
 * 
 * Time: O(sqrt(n)). Space: O(1)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

int num_tc, n, a, t;
int main(){
    scanf("%d", &num_tc);
    for (int tc=0; tc<num_tc; tc++){
        scanf("%d", &n);
        n = n*2;
        a = t = 0;
        for (int i=2; i<=sqrt(n); i++){
            if (n%i == 0){ // i is a factor and n/i is a factor
                if (((n/i - i + 1) & 1) == 0){ // n/i -i + 1 is even
                    a = (n/i + 1 - i)/ 2;
                    t = i;
                    break;
                }
            }
        }
        if (t == 0){
            printf("IMPOSSIBLE\n");
            continue;
        }

        printf("%d = ", n/2);
        for (int i=a; i<t+a-1; i++){
            printf("%d + ", i);
        }
        printf("%d\n", t+a-1);
    }

    return 0;
}