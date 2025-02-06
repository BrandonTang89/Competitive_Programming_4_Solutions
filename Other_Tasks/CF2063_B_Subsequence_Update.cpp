#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
vector<ll> arr;

ll checkOut(int takeL, int takeR, int solveL, int solveR){
    int i = takeL;
    int j = solveR;

    ll ans = 0;
    while (i <= takeR && j >= solveL && arr[i] < arr[j]){
        ans += (arr[i] - arr[j]);
        i++;
        j--;
    }

    return ans;

}
int main(){
    int tc;
    cin >> tc;
    while(tc--){
        int l, r;
        
        cin >> n >> l >> r;
        l--; r--;
        arr.resize(n);
        for(int i = 0; i < n; i++){
            cin >> arr[i];

        }


        if (l > 0) sort(arr.begin(), arr.begin() + l);
        sort(arr.begin() + l, arr.begin() + r + 1);
        if (r < n-1) sort(arr.begin() + r + 1, arr.end());
        
        ll originalSum = 0;
        for(int i = l; i <= r; i++){
            originalSum += arr[i];
        }

        ll ans = originalSum + min(checkOut(0, l - 1, l, r), checkOut(r + 1, n - 1, l, r));
        cout << ans << endl;
    }

    return 0;
}