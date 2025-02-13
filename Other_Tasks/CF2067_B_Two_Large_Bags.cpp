#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;

int main(){
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        vector<int> v(n);
        map<int, int> m;
        for (int i = 0; i < n; i++){
            cin >> v[i];
            m[v[i]]++;
        }

        int prev = -1;
        int prevNum = 0;
        bool can = true;
        while (!m.empty()){
            int val = m.begin()->first;
            int num = m.begin()->second;
            m.erase(m.begin());

            if (prev + 1 == val){
                num += prevNum;
            }
            else if (prevNum > 0){
                m.insert({val, num});
                val = prev + 1;
                num = prevNum;
            }

            if (num == 1){
                can = false;
                break;
            }
            num -= 2;
            prev = val;
            prevNum = num;
        }
        if (prevNum % 2 == 1){
            can = false;
        }

        cout << (can ? "Yes" : "No") << endl;

    }

    return 0;
}