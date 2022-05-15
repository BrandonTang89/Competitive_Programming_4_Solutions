/**Kattis - nonprimefactors
 * Relatively simple modification to the sieve to generate the number of divisors of a number.
 * Then for each query, just output numDivisors - numDiffPF
 * 
 * Time: O(n log n) (approximately for sum of harmonic series)
 * Space: O(n)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> numDiffPF;
void fill_numDiffPF(int _upperbound) {
    numDiffPF.assign(_upperbound, 0);
    for (int i = 2; i <= _upperbound; i++) {
        if (numDiffPF[i] == 0) {  // i is prime
            for (int j = i; j <= _upperbound; j += i) {
                numDiffPF[j]++;  // j is divisible by prime i
            }
        }
    }
}

vector<int> numDivisors;
void fill_numDivisors(int _upperbound){
    numDivisors.assign(_upperbound, 0);
    for (int i=1; i<= _upperbound; i++){
        for (int j=i; j<= _upperbound; j+=i){
            numDivisors[j] += 1;
        }
    }
}
int main(){
    fill_numDiffPF(2e6 + 5);
    fill_numDivisors(2e6 + 5);

    int q, n;
    scanf("%d", &q);
    for (int query = 0; query < q; query++) {
        scanf("%d", &n);
        printf("%d\n", numDivisors[n] - numDiffPF[n]);
    }

    return 0;
}