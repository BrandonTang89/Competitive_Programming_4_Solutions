/* Kattis - Geppetto
A relatively basic combination complete search question, iterate over 2^N possible subsets of ingredients
for each subset, check whether each of the rules are violated. Use bitmask since N<=20<31.

Observation 1:
    Since there could be many repeated and/or equivalent rules, ensure that we store the rules as a,b where a<b
    and remove duplicates using set

Time: O(2^n * m)
Mem: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
int a, b;
set<pair<int,int>> s;
int main(){
    cin >> n >> m;
    for (int i=0;i<m;i++){
        cin >> a >> b;
        a--; b--; // 0 index for easier bit mask
        if (a > b){
            swap(a,b); // a < b to prevent (a,b) (b,a) being in s
        }
        s.insert(make_pair(a,b));
    }

    int total_valid = 0;
    for (int bm=0; bm<(1<<n); bm++){
        bool valid = true;
        for (auto p: s){
            a = p.first;
            b = p.second;
            bool both_on_pizza = ((bm & (1<<a)) && (bm &(1<<b)) );
            //printf("a: %d, b: %d, bop: %d\n",a,b, both_on_pizza);
            if (both_on_pizza){
                valid = false;
                break;
            }

            if (!valid)break;
        }

        if(valid)total_valid++;
    }

    cout << total_valid << endl;
}