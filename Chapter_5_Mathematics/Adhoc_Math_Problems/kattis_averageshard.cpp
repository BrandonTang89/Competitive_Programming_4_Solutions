/**Kattis - averageshard
 * We just check for each CS student, whether his IQ is lower than the average for CS students
 * but greater than the average for economics students. If so, ans++
 * 
 * Time: O(cs + econs), Space: (cs)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int num_tc, cs, econs;
ll temp;
ll total_cs=0, total_econs=0;
vector<ll> v;
long double avg_cs, avg_econs;
int main(){
    cin >> num_tc;
    for (int tc=0;tc<num_tc; tc++){
        v.clear();
        total_cs = total_econs = 0;
        cin >> cs >> econs;

        for (int i=0; i <cs; i++){
            cin >> temp;
            v.push_back(temp);
            total_cs += temp;
        }
        avg_cs = total_cs/(double)cs;
        for (int i=0; i <econs; i++){
            cin >> temp;
            total_econs += temp;
        }
        avg_econs = total_econs/(double)econs;

        int ans = 0;
        for (auto i: v){
            if (i < avg_cs && i > avg_econs){
                ans++;
            }
        }
        cout << ans <<endl;
    }
    return 0;
}