/* Kattis - promotions
Observation 0:
    There are clearly 2 parts to the task
        1. find the number of people who MUST PROMOTE at a and b
        2. find the number ofpeople who CAN NEVER PROMOTE at b

    Looking at the input bounds, we can see that actually VE = 10000^2 which is a reasonable amount..
    Given that we are doing O(V + E) dfs, an O(V^2 + VE) algorithm might be what the problem author
    is looking for.

Observation 1:
    For a given employee i, we can do run kahn's algorithm to determine how many people can be promoted
    assuming unlimited promotions, but given that employee i remains unpromoted.

    If the number of promotions is less than a, it means that to promote a people, employee i needs 
    to be promoted. Similarly, if num_promoted[i] < b, employee i needs to be promoted to promote b
    employees.

    We can try not promoting employees 1 by 1, and then afterwards seeing how many employees have
    num_promoted[i] < a or < b. This will run in O(V^V + VE)

Observation 2:
    If we promote an employee, all employees in the DFS spanning tree of the transpose of the orignal
    graph also must be promoted. Thus we can calculate the minimum number of promotions needed to
    promote a specific employee.

    As such, for each employee, we run our DFS algorithm, counting the number of nodes visited as we go.
    We then find the number of employees which need more than b promotions to be able to promote.
    This also occurs in O(V^2 + VE)

Observation 3:
    There are ways to speed up the algorithms by using dynamic programming. We note that if an employee
    i has num_promoted[i] < a, all ancestors of i also have num_promoted[j] < num_promoted[i] < a.
    This is because the ancestors would have to be promoted for a to be promoted anyway. 

    Similarly, we note that if i cannot be promoted in b promotions,
    all successors of i also cannot be promoted in b promotions.

    Of course, with these memorisation techniques, there is still the worst case scenario where we always
    select a node that doesn't provide information on other nodes. However, if we perform this on nodes in a
    random order, the probability of this occuring is minimal.

    However, this observation is not required for AC and thus is not implemented here.

Time: O(V^2 + VE), Mem: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, e, u, v, a, b;
vi adjlist[5009], adjlist_t[5009]; 

// Kahn algorithm variables
queue<int> q;
vi in_deg, in_deg_use, num_promoted;

// dfs variables
vector<bool> visited;
int promotion_counter;
void dfs(int u){
    visited[u] = 1;
    promotion_counter++;
    for (auto v: adjlist_t[u]){
        if (visited[v]) continue;
        dfs(v);
    }
}

int main(){
    fast_cin();
    cin >> a >> b >> n >> e;
    in_deg.assign(n, 0);
    
    for (int i=0;i<e;i++){
        cin >> u >> v;
        adjlist[u].emplace_back(v);
        adjlist_t[v].emplace_back(u);
        in_deg[v]++;
    }

    //for (auto i:in_deg){cout << i << " ";}cout << endl;

    num_promoted.assign(n, 0); // number of people who could possibly be promoted if i remains unpromoted
    for(int i=0;i<n;i++){
        in_deg_use = in_deg;
        for (u=0;u<n;u++){
            if (in_deg_use[u] == 0){
                q.push(u);
            }
        }
        while (!q.empty()){
            u = q.front(); q.pop();
            if (u == i)continue;
            
            num_promoted[i]++;
            for (auto v: adjlist[u]){
                in_deg_use[v]--;
                if (in_deg_use[v] == 0)q.push(v);
            }
        }
    }
    //for (auto i: num_promoted){cout << i << " ";}cout << endl;

    int min_gaurantee_promote = 0, max_gaurantee_promote = 0;
    for (int i=0;i<n;i++){
        if (num_promoted[i] < a)min_gaurantee_promote++; // i needs to be promoted to hit a promotions
        if (num_promoted[i] < b)max_gaurantee_promote++;
    }
    cout << min_gaurantee_promote << endl;
    cout << max_gaurantee_promote << endl;

    int num_cannot_promote = 0;
    for (int i=0;i<n;i++){
        visited.assign(n, 0);
        promotion_counter = 0;
        dfs(i);
        if (promotion_counter > b){
            num_cannot_promote++;
        }
    }
    cout << num_cannot_promote << endl;
    return 0;
}