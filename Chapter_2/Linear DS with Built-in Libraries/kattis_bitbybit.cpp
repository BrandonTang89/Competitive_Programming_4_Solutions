/*
Kattis - BitbyBit
This is a adhoc/bit manipulation question that has a bunch of tricky cases to spot. Do it carefully and it should be no problemo

Time: O(n*TC) Mem: O(1) 
*/

#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    int arr[32];
    while (true){
        cin >>  n;
        if (n == 0)break;

        for (int i=0;i<32;i++)arr[i] = -1;

        string op;
        int v, u;

        for(int i=0;i<n;i++){
            cin >> op >> v;
            if (op == "SET")arr[v] = 1;
            else if (op == "CLEAR")arr[v] = 0; 
            else if (op == "AND"){
                cin >> u;
                if (arr[u] != -1 && arr[v] != -1)arr[v] = arr[v]&arr[u];
                else if (arr[u] == 0 || arr[v] == 0) arr[v] = 0; // aif either are 0
                else if (arr[u] == -1 && arr[v] == 1)arr[v] = -1;
            }
            else if (op == "OR"){
                cin >> u;
                if (arr[u] != -1 && arr[v] != -1)arr[v] = arr[v]|arr[u];
                else if (arr[u] == 1 || arr[v] == 1) arr[v] = 1;
                else if (arr[u] == -1 && arr[v] == 0)arr[v] = -1;
            }
        }

        
        for (int i=31;i>=0;i--){
            if (arr[i] != -1)
                cout << arr[i];
            else cout << "?";
        }
        cout << endl;

    }

    return 0;
}