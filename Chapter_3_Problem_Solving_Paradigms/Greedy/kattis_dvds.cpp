/* Kattis - dvds

Observation 1:
    Note that given an example permutation of {5 1 2 4 3}, 1 2 3 are already sorted relative to each other.
    Thus we only need to move the other 2 numbers. These other 2 numbers can each be put into their position in 1
    move (move 4 followed by 5). In general, we find out how many numbers in the sorted sequence are already appearing
    in the correct order (1, 2, 3, ... ) ignoring wrongly ordered numbers. Then we move each number that is in the wrong
    relative order in ascending order.

    This is optimal because for each move we do, we can at most change the relative position of 1 item anyway. So if
    we need to change the position of x elements, we minimally need x moves. Since the above algorithm will work and
    only uses x moves, it is optimal.

Time: O(nk), Mem: O(1)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;
 
typedef long long ll;
typedef long double ld;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
 
int n, k, dummy;
int main(){
    fast_cin();
    cin >> k;
    for (int tc=0;tc<k;tc++){
        cin >> n;
        int ans = 0;
        int counter = 1;
        for (int i=0;i<n;i++ ){
            cin >> dummy;
            if (dummy == counter){
                counter++;
            }
            else{
                ans++;
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}