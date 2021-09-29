/* Kattis - blackfriday
Not sure if this problem was supposed to be here and not in the easy problem section. 
It's solution is direct and obvious

Time: O(n), Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

int counter[6];
int arr[101];

int main(){
    int n;
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> arr[i];
        counter[arr[i] -1]++;
    }
    
    int higher_unique = -1;
    for (int i=0;i<6;i++){
        //cout << " counter " << i << " " << counter[i] << endl;
        if (counter[i] == 1){
            
            higher_unique = max(higher_unique, i);
        }
    }

    //cout << "higher unique " << higher_unique << endl;
    if (higher_unique == -1){
        cout << "none" << endl;
    }
    else{
        for (int i=0;i<n;i++){
            if (arr[i] == higher_unique+1){
                cout << i+1 << endl;
            }
        }
    }

    return 0;
}