#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


int main(){
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++){
            cin >> arr[i];
        }

        vector<int> oriRate(n); // original rating after looking through arr[0].. arr[i]

        int x = 0;
        for (int i = 0; i < n; i++){
            if (arr[i] > x) x++;
            else if (arr[i] < x) x--;
            oriRate[i] = x;
        }

        vector <int> brr(n); // max rating post arr[0]..arr[i] assuming at least 1 skip
        int cur = 0;
        for (int i=0; i<n; i++){
            brr[i] = cur;
            cur = max(cur, (oriRate[i]));
        }

        vector<int> crr = brr;
        for (int i=0; i<n-1; i++){
            int nx = crr[i];
            if (arr[i+1] > nx) nx++;
            else if (arr[i+1] < nx) nx--;
            crr[i+1] = max(crr[i+1], nx);
        }   

        cout << crr[n-1] << endl;

    }

    return 0;
}