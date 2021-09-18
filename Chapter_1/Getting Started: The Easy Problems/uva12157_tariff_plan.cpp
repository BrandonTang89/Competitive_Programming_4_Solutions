// UVa 12157 Tariff Plan - Accepted
// Compare 2 plans to see what is the cheapest. Time O(total_tc * n), Mem O(1)
#include <bits/stdc++.h>
using namespace std;


int miles(int n){
    int ans = (n/30 + 1)*10;

    //cout << "mile("<< n << ") = " << ans << endl;
    return ans;
}

int juice(int n){
    int ans = (n/60 + 1)*15;

    // cout << "juice("<< n << ") = " << ans << endl;
    return ans;
}

int total_tc, n, k;
int main(){
    cin >> total_tc;
    for(int t=0; t<total_tc; t++){
        cin >> n;
        int total_miles, total_juice;
        total_miles = total_juice = 0;

        for (int i=0;i <n;i++){
            cin >> k;
            total_miles += miles(k);
            total_juice += juice(k);
        }

        // cout << "total_miles " << total_miles << endl;
        // cout << "total_juice " << total_juice << endl;

        string best_plan;
        int min_cost = 0;
        if (total_miles < total_juice){
            best_plan = "Mile";
            min_cost = total_miles;
        }
            
        if (total_miles > total_juice){
            best_plan = "Juice";
            min_cost = total_juice;
        }
        if (total_miles == total_juice){
            best_plan = "Mile Juice";
            min_cost = total_miles;
        }

        cout << "Case " << t+1 << ": " << best_plan << " " << min_cost << endl;
        
    }
    return 0;
}