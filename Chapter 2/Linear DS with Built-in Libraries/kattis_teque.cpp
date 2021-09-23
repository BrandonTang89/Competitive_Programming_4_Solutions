/* Kattis - Teque

Observation 1:
    Most of the operations needed (except the push middle) are already implemented into STL deque, so we should make use of it
    Regarding pushing into the middle, we can just use 2 seperate deques that each contain the left and right half of the teque
    
    Push middle is then simply to push into the left deque back

    after every operation, we should balance the left and right deques such that the size of the left deque is at most one greater than
    that of the right deque

Time: O(n), Mem: O(n)
*/
#include<bits/stdc++.h>
using namespace std;

deque<int>ld, rd;
int n, m;

string op;
int main(){
    scanf("%d", &n);
    for (int op_num=0; op_num<n; op_num++){
        char ope[12];
        scanf("%s %d", ope, &m);
        op = ope;

        if (op == "push_front"){
            ld.push_front(m);
        }
        else if (op == "push_back"){
            rd.push_back(m);
        }
        else if (op == "push_middle"){
            ld.push_back(m);
        }
        else{
            int index=m;
            if (index>= ld.size()){
                index -= ld.size();
                printf("%d\n", rd[index]);
            }
            else{
                printf("%d\n", ld[index]);
            }
        }


        while (ld.size() > rd.size() +1){
            rd.push_front(ld[ld.size()-1]);
            ld.pop_back();
        }
        while (rd.size() > ld.size()){
            ld.push_back(rd[0]);
            rd.pop_front();
        } 

        /*        
        for(auto i:ld){
            cout << i << " ";
        }cout << "| ";
        for(auto i:rd){
            cout << i << " ";
        }cout << endl;*/

    }

    return 0;
}