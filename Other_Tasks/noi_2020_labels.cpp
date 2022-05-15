/**NOI 2020 Finals Question 1 - labels
 * https://dunjudge.me/analysis/problems/2122/
 * Just simply start from an arbitary value, then see what the spread between the largest and smallest value is.
 * It has to be exactly n for for the sequence to be unique.
 * 
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
int main(){
    fast_cin();
    cin >> n;
    vector<int> A;
    A.resize(n);
    A[0] = 0;
    int largest = 0, smallest = 0;
    for (int i=1; i<n; i++){
        cin >> A[i];
        A[i] += A[i-1];
        largest = max(largest, A[i]);
        smallest = min(smallest, A[i]);
    }
    if (largest-smallest+1 != n){
        cout << -1 << endl;
        return 0;
    }

    for (int i=0; i<n; i++){
        cout << A[i]+(1 - smallest) << " ";
    }
    cout << endl;

    return 0;
}