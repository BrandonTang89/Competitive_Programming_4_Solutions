/*
Kattis - Pairingsocks

Observation 1:
    We only need to do a linear pass on the original stack using the first 2 possible operations to 
        1. check if it is possible and to 
        2. count the minimum number of moves
    
    proof for 1:
        if there exists a stack that can be solved with the use of the third operation, it means there exist 2 adjacent same pair of socks in the aux pile
        when we were processing those 2 socks, they would have been on the tops of both piles at one point
        thus it is not possible to exist such as stack
    proof for 2:
        since the third operation is not used, the number of socks in the original pile is always decreasing by 1 each move
        this results in the minimum number of moves possible as there is no combination of moves that reduces the
        number of socks in the original pile by more than 1 per move

    This is very similar to the bracket matching algorithm that is commonly talked about

Time: O(n) Mem: O(n) 
*/

#include <bits/stdc++.h>
using namespace std;

int n, temp;
stack<int> ori, aux;
int main(){
    cin >> n;
    
    for (int i=0;i<2*n;i++){
        cin >> temp;
        aux.push(temp);
        
    }
    
    for (int i=0;i<2*n;i++){
        ori.push(aux.top());
        aux.pop();
    }
    
    long long mc = 0;
    while (!ori.empty()){
        if (!aux.empty()){
            if (aux.top() == ori.top()){
                mc++;
                aux.pop();
                ori.pop();
            }
            else{
                mc++;
                aux.push(ori.top());
                ori.pop();
            }
        }
        else{
            mc++;
            aux.push(ori.top());
            ori.pop();
        }
    }
    if (aux.empty()){
        cout << mc << endl;
    }
    else cout << "impossible" << endl;
    
    return 0;
}