// UVa 12696 Cabin Baggage
// Some basic logical operators. Time O(1), Mem O(1)
#include <bits/stdc++.h>
using namespace std;

int t; 
double l, w, d, weight;
int main(){
    cin >> t;
    int total = 0;
    for(int i=0;i<t;i++){
        cin >> l >> w >> d >> weight;

        bool allowed = false;

        //cout << l+w+d << endl;
        
        if (((l <= 56 && w <= 45 && d <= 25) || (l+w+d <= 125) ) && weight <= 7)allowed = true;

        cout << (int) allowed << endl;
        total += allowed;
    }

    cout << total << endl;
    return 0;
}