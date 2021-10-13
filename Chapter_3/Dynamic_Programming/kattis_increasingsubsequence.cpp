/* Kattis - increasingsubsequence

Classic LIS with printing the lexicographically smallest LIS. Note that this code should not be used for template
code, there are many better implementations online.

Time: O(n log k), k is the length of the LIS
Mem: O(n)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef long double ld;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, pos, lis_end=0;
int arr[201];
vector<int> l; // l[i] contains the smallest ending of a i-LIS
vector<int> l_id; // l_id[i] contains the index of the element in l[i]
vector<int> p; // p[i] contains the index of the parent element of the LIS ending at arr[i]

int main(){
    while (true){
        cin >> n;
        if (n == 0)break;
        l.clear();
        l_id.clear();
        p.clear();
        for (int i=0;i<n;i++){
            
            cin >> arr[i];            
            auto it = lower_bound(l.begin(), l.end(), arr[i]);
            if (it == l.end()){ // expand
                l.push_back(arr[i]);
                l_id.push_back(i);
                p.push_back((i != 0) ? l_id[l.size()-2] : -1); // edge case of i == 0
                lis_end = i;
            }
            else{
                pos = it - l.begin();
                l[pos] = arr[i];
                l_id[pos] = i;
                p.push_back(pos ? l_id[pos-1] : -1); // -1 if the smallest element
                if (pos == (int) l.size() - 1)lis_end = i;
            }

            //for (auto i:l){cout << i << " ";}cout << endl;
        }
        cout << l.size() << " ";
            
        //for (int i=0;i<n;i++){cout << p[i] << " ";} cout << endl;
        
        vector<int> v;
        for (int i=lis_end; i!=-1; i = p[i]){
            v.push_back(arr[i]);
        }
        reverse(v.begin(), v.end());
        for(int i=0;i<(int) v.size()-1; i++){
            cout << v[i] << " ";
        }cout << *--v.end() << endl;
        

    }

   return 0;
}