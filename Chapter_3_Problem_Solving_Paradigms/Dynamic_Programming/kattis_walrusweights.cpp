/* Kattis - walrusweights
This DP question is closely related to knapsack / coin change.

Observation 1:
    Note that there is theoratically no upperbound on the total weight, but note that if the total weight
    goes above 2000, we might as well take 0 weight! So we can just prune all of those solutions away, resulting
    in our weight only varying between 0 and 2000, allowing for DP to have a reasonable number of states.

This problem also involves backtracking to find the actual weights taken, but we have seen this kind of problem
many times already so its just more of the same thing :)

Time: O(n * 2000), Mem: O(n * 2000)
*/ 
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, weight; 
vector<int>weights;
long long memo[1000+9][2009]; //note if weight > 2000, just prune already

long long dp(int id, int w){
    if (id == n)return abs(w - 1000); // finished

    long long &ans = memo[id][w];
    if (ans != -1)return ans;
    if (w + weights[id] > 2000)return ans = dp(id+1, w); // obviously not good to take
    return ans = min(dp(id+1, w),  dp(id+1, w+weights[id])); // take or dont take
}

int actual_weight = 0;
void fill_actual_weight(int id, int w){
    if (id == n)return;

    if (dp(id+1, w+weights[id]) == dp(id, w)){ //take the extra weight if it still gives the optimal outcome
        actual_weight += weights[id];
        fill_actual_weight(id+1, w+weights[id]);
    }
    else{
        fill_actual_weight(id+1, w);
    }
    return;
}


int main(){
	memset(memo, -1, sizeof(memo));
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> weight;
        weights.emplace_back(weight);
    }
    fill_actual_weight(0,0);
    cout << actual_weight << endl;
    
}