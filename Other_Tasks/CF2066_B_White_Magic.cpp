#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;

int n;
multiset<int> s;
int main(){
    int tc;
    cin >> tc;
    while(tc--){
        cin >> n;
        vector<int> arr(n);
        s.clear();
        int numZeros = 0;
        int firstZero = -1;
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            s.insert(arr[i]);

            if (arr[i] == 0){
                numZeros++;
                if (firstZero == -1){
                    firstZero = i;
                }
                else{
                    s.erase(s.find(0));
                }
            }
        }
        if (numZeros == 0){
            cout << n << endl;
            continue;
        }

        int mex = 0;
        while(s.find(mex) != s.end()){
            mex++;
        }
        
        // We try the whole sequence with the first zero (exclude all the other zeros)
        bool can = true;
        int mini = INT_MAX;
        for (int i=0; i<n; i++){
            if (arr[i] == 0){
                break;
            }
            
            mini = min(mini, arr[i]);
            s.erase(s.find(arr[i]));
            if (arr[i] < mex && s.find(arr[i]) == s.end()){
                mex = arr[i];
            }

            if (mini < mex){
                can = false;
                break;
            }
        }

        if (can){
            cout << n - numZeros + 1<< endl;
        }
        else{
            cout << n - numZeros << endl;
        }
    }

    return 0;
}