#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
vector<vector<int>> arr;

int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        arr.assign(2, vector<int>(n, 0));
        for (int r = 0; r <= 1; r++) {
            for (int i = 0; i < n; i++) {
                char c;
                cin >> c;
                arr[r][i] = c - '0';
            }
        }

        vector<int> route;

        int r=0, c=0;
        while (c < n) {
            route.push_back(arr[r][c]);
            if (c == n-1){
                if (r == 0){
                    r++;
                    continue;
                }
                else{
                    break;
                }
            }


            if (r == 1){ // just move along
                c++;
            }
            else{
                if (arr[1][c] < arr[0][c+1]){
                    r++;
                }
                else{
                    c++;
                }
            }
        }

        for (int i = 0; i < route.size(); i++) {
            cout << route[i];
        }
        cout << endl;

        vector<vector<int>> count(2, vector<int>(n, 0));
        count[1][n-1] = 1;
        for (int r=1; r>=0; r--){
            for (int c=n-1; c>=0; c--){
                // check whether the cell is valid:
                int idx = r + c;
                bool valid = (route[idx] == arr[r][c]);

                if (!valid) continue;

                if (c < n-1){
                    count[r][c] += count[r][c+1];
                }
                if (r == 0){
                    count[r][c] += count[r+1][c];
                }

            }
        }
        cout << count[0][0] << endl;
    }

    return 0;
}