#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);



int main(){
    int tc;
    cin >> tc;
    while (tc--){
        int n;
        cin >> n;
        string s;
        cin >> s;

        priority_queue<int> pq;
        ll cost = 0;
        for (int i=n; i>0; i--){
            if (s[i-1] == '1'){
                pq.push(i);
            }
            else{
                if (!pq.empty()){
                    pq.pop();
                }
                cost += i;
            }
        }

        vector<int> v;
        while (!pq.empty()){
            v.push_back(pq.top());
            pq.pop();
        }
        for (int i=v.size()/2; i<v.size(); i++){
            cost += v[i];
        }
        cout << cost << endl;
    }

    return 0;
}