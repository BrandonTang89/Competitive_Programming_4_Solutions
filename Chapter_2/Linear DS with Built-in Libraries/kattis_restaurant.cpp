/*
Kattis - Restaurant
A relatively easy question (that i somehow found annoyingly hard to debug)
The trick is to always move plates to stack 2 and take plates from stack 1.
You should only transfer plates from stack 2 to 1 when stack 1 is empty.
i.e. you might need to split the TAKE operation into (take, move, take)

Time: O(TC n), Mem: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

long long n, m, s1_c, s2_c;
string op;
int main(){
    
    while (true){
        cin >> n;
        //cout << "n " << n << endl;
        if (n==0)break;
        s1_c = s2_c = 0;
        for (int e=0;e<n;e++){
            cin >> op >> m;
            if (op == "DROP"){
                printf("DROP 2 %lld\n", m); 
                s2_c += m;

            }
            else if (op == "TAKE"){
                if (s1_c >= m){
                    s1_c -= m;
                    printf("TAKE 1 %lld\n", m);
                }
                else{
                    if (s1_c != 0){ 
                        printf("TAKE 1 %lld\n", s1_c);
                        m -= s1_c;
                        s1_c = 0;
                    }

                    printf("MOVE 2->1 %lld\n", s2_c);
                    s1_c = s2_c - m;
                    s2_c = 0;
                    printf("TAKE 1 %lld\n", m);
                    
                }

            }
        }
    
        printf("\n");
        
    }
    
}
