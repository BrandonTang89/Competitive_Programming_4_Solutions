/* Kattis - Knapsack
Classic Knapsack but with printing optimal solution.

Time: O(nc), Mem: O(nc)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;
int c, n;
int w, v;

vector<pair<int,int>>items; // value, weight
// dp(index, rw) is the max val considering all items <= index with a remaining weight of rw

long long memo[2002][2002];
long long dp(int index, int rw){ //
    //printf("index: %d, rw: %d\n", index, rw);
    if ((index == n) || (rw == 0))return 0;
    long long &ans = memo[index][rw];
    if (ans != -1)return ans;

    // either get it or not
    if (rw < items[index].second){ //cannot contain current item
        return ans = dp(index+1, rw);
    }
    
    return ans = max(dp(index+1, rw), items[index].first + dp(index+1, rw-items[index].second)); 
}

vector<int> selected_indices;
void fill_selected_indices(int index, int rw){
    if (index == 0)selected_indices.clear();
    if (index == n)return;
    
    if (dp(index, rw) == dp(index+1, rw) ){ // if we can, just don't take this item
        fill_selected_indices(index+1, rw);
    }
    else{
        selected_indices.emplace_back(index);
        fill_selected_indices(index+1, rw-items[index].second);
    }
    return;
}
int main(){
    while (scanf("%d %d", &c, &n) != EOF){
        memset(memo, -1, sizeof(memo));
        items.clear();

        for (int i=0;i<n;i++){
            scanf("%d %d", &v, &w);
            items.emplace_back(v, w);
        }

        fill_selected_indices(0, c);
        printf("%d\n", selected_indices.size());
        for (int i=0;i<(int)selected_indices.size() - 1;i++){
            printf("%d ", selected_indices[i]);
        }
        if (selected_indices.size() > 0){
            printf("%d\n", *--selected_indices.end());
        }
    }


   return 0;
}