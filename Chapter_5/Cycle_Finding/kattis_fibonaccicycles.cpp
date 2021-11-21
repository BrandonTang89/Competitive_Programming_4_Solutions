/**Kattis - fibonaccicycles
 * Cyle finding using a DAT since the modulus is small. Read the question properly to understand
 * the value they want your program to return.
 * 
 * Time: O(m), Space: O(m)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

vector<int> visited;
int q, m; // modulo
int main(){
    scanf("%d", &q);
    for (int tc=0; tc<q; tc++){
        scanf("%d", &m);
        int fib_sl = 1, fib_l = 1;
        
        visited.assign(m+1, -1);
        int n = 1;
        while (true){
            int fib_next = (fib_sl + fib_l) % m;
            n++;
            if (visited[fib_next] != -1){
                printf("%d\n", visited[fib_next]);
                break;
            }
            visited[fib_next] = n;
            fib_sl = fib_l;
            fib_l = fib_next;
        }

    }
    return 0;
}