/* Kattis - Orders

In CP4 this is listed as a knapsack problem, but really its essentially just
coin change counting variant with printing of the solution if it is unique.

Debugging:
    Long long for DP and Memo table since there are so many ways to make changes

Time: O(nc), Mem: O(nc)
*/ 
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, m, c, item;
vector<int>items;
long long memo[119][30019];

long long dp(int id, int val){ // number of ways to construct value with items >= id
    if (val == 0) return 1; // just nth :)
    if (id == n || val < 0)return 0; // impossible

    long long &ans = memo[id][val];
    if (ans != -1)return ans;

    return ans = dp(id+1, val) + dp(id, val-items[id]); // move on or take one more
}

vector<int> selected_items;
void fill_selected_items(int id, int val){
    //printf("id: %d, val: %d, dp(id, val): %d, dp(id+1, val): %d\n", id, val ,dp(id,val), dp(id+1, val));
    if (val == 0)return;
    if (dp(id+1, val) == (long long) 1){ // we can move on
        fill_selected_items(id+1, val);
    }
    else{
        //cout << "adding index " << id << endl;
        selected_items.emplace_back(id);
        fill_selected_items(id, val-items[id]);
    }
}

int main(){
    fast_cin();
    cin >> n;
    memset(memo, -1, sizeof(memo));
    for (int i=0;i<n;i++){
        cin >> item;
        items.emplace_back(item);
    }

    cin >> m;
    for (int i=0;i<m;i++){
        cin >> c;
        if (dp(0, c) == 0){
            cout << "Impossible" << endl;
        }
        else if (dp(0, c) > 1){
            cout << "Ambiguous" << endl;
        }
        else{ // generate unique solution
            selected_items.clear();
            fill_selected_items(0, c);
            for (int i=0;i<(int)selected_items.size();i++){
                cout << selected_items[i]+1 << ((i != (int) (selected_items.size() - 1)) ? ' ' : '\n');
            }
        }
    }

   return 0;
}