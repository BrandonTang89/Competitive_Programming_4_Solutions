/* Kattis - kutevi
An interesting bottom up dp with the potential for much mathy speedups

Observation 1:
    if we start at a specific angle (a) and keep adding a fixed angle (d), we will end up with a + x(d) mod 360.
    We know that when x == 360, we will end up back at a. This means that actually that actually adding d multiple
    times results in a loop. So we don't have to care about subtracting d from a, since when x == 359, we get
    a - d (mod 360). Similar arguments could be made for subtracting d from a multiple times.

Observation 2:
    So how exactly do we choose specific angles a and d? Well, starting with a == 0, we choose d to be the first makeable
    angle. So we already have all xd. We can then move on to the next angle, e and then for each already makeable angle,
    apply the loop to generate all angles of the form xd + ye for all x and y.
    
    This process will be repeated for all initial values, allowing us to make all the possible angle :)

Time: O(n * 360*360), Mem: O(1)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

bool can_make[369];
vector<int> initial;
int n, q, ang, counter;

int main(){
    fast_cin();
    cin >> n >> q;
    for (int i=0;i<n;i++){
        cin >> ang;
        initial.emplace_back(ang);
    }
    can_make[0] = true;

    for (int i=0;i<n;i++){
        ang = initial[i];
        for (int k=0; k<360;k++){
            if (can_make[k]){
                for (int j=(ang+k)%360;  j != k; j = (j + ang)%360){ // loop until we arrive back at k
                    can_make[j] = true;
                }
            }
        }
        
    }

    for (int i=0;i<q; i++){
        cin >> ang;
        cout << (can_make[ang] ? "YES" : "NO") << endl;
    }


   return 0;
}