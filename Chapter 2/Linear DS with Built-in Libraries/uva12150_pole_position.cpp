// UVA 12150 Pole Position
// Basic Array manipulation, Time: O(n), Mem: O(n)
#include <bits/stdc++.h>
using namespace std;

bool can_do;
int n, c, p;
int start[10009];

int main(){
    while (true){
        can_do = true;
        memset(start, 0, 10009);
        cin >> n;
        if (n==0)break;
        for (int i=0;i<n;i++){
            cin >> c >> p;
            if (i+p < 0 || i+p >= n){
                can_do = false;
                continue;
            }
            if (start[i+p] == 0){
                
                start[i+p] = c;
            }
            else{
                can_do = false;
            }
        }

        if (!can_do){
            cout << -1 << endl;
        }
        else{
            for (int i=0;i<n-1;i++){
                cout << start[i] << " ";
            }
            cout << start[n-1] << endl;
        }
    }


    return 0;
}