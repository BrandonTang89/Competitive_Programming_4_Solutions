/* Kattis - bookclub
This is a basic MCBM question. There was no need for greedy pre-processing speed up.

Observation 1:
    Ignore whatever the question about cycles and stuff. We will model the task as a biparitite
    graph of 2*n nodes. The left nodes are the n people and the right side are the n books.
    There exist an edge from person i to book j if person i wants book j. We are finding out
    whether we can match each person to each book perfectl, ie MCBM

Time: O(VE), Mem: O(V+E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


// left is the people, right is the books. L->R exist if person L wants book R
int n, e, u, v;
vector<vector<int>> adjlist;
vector<int> match, visited;

// MCBM Augmenting Path Algorithm
int aug(int L){
    if (visited[L]) return 0;
    visited[L] = 1;
    for (auto &R : adjlist[L]){
        if (match[R] == -1 || aug(match[R])){
            match[R] = L;
            return 1;
        }
    }
    return 0;
}

int main(){
    cin >> n >> e;
    adjlist.assign(2*n, vector<int>());
    for (int i=0;i<e;i++){
        cin >> u >> v;
        adjlist[u].emplace_back(v+n);
        adjlist[v+n].emplace_back(u);
    }
    match.assign(2*n, -1);
    int MCBM = 0;
    for (int L=0;L<n;L++){
        visited.assign(2*n, 0);
        MCBM += aug(L);
    }
    //cout << MCBM << endl;
    cout << ((MCBM == n) ? "YES" : "NO") << endl; 
    return 0;
}