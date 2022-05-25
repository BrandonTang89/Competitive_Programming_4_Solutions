/**Kattis - towering
 * Easy iterative complete search question. Just do it.
 * 
 * Time: O(1), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int th1, th2;
vector<int> h(6);
int main(){
    for (int i=0; i<6; i++) cin >> h[i];
    cin >> th1 >> th2;
    sort(h.begin(), h.end());

    do{
        if (h[0] + h[1] + h[2] == th1 && h[3] + h[4] + h[5] == th2){
            if (h[0] > h[1] && h[1] > h[2]){
                if (h[3] > h[4] && h[4] > h[5]){
                    for (int i=0; i<6; i++) cout << h[i] << " ";
                    return 0;
                }
            }
        } 
    }while (next_permutation(h.begin(), h.end()));

    return 0;
}