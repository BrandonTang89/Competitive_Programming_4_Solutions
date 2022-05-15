/* Kattis - Tautology

Observation 1:
    The WFF is given in pre-fix format... but we already know it is easier to deal with post fix...
    If we reverse the WFF, we almost get post-fix, but for each operation, the operands are swapped.
    But, does that matter here? NO! because we will check all possibilities of inputs anyway, so even if
    operand x and y are swapped, we will eventually check the unswapped version sometime else

Design 1:
    Use bitmask and bit operations to easily and quickly iterate the 2^5 different possibilities,
    using a map to map the chars to constant positions of the bitmask

Time: O(2^5 * len(WFF)) == O(len(WFF))
Mem: O(len(WFF))
*/
#include <bits/stdc++.h>
using namespace std;

string wff;
stack <bool> s;
map<char,int> m; // maps p, q, r, s, t to bit mask bits
int main(){
    m['p'] = 0;
    m['q'] = 1;
    m['r'] = 2;
    m['s'] = 3;
    m['t'] = 4;

    while (true){
        cin >> wff;
        if (wff == "0")break;
        reverse(wff.begin(), wff.end()); //to get it into post-fix

        bool taut = true;
    
        for (int bm=0; bm<(1<<5); bm++){ // bitmask with 5 bits
            //while(!s.empty())s.pop();
            for (auto c:wff){
                if (c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't'){
                    s.push((bm & (1 << m[c])) == (1 << m[c]));
                }
                else if (c == 'N'){
                    bool temp = !s.top();
                    s.pop();
                    s.push(temp);
                }
                else if (c == 'A'){
                    bool temp1 = s.top();
                    s.pop();
                    bool temp2 = s.top();
                    s.pop();

                    s.push(temp1 | temp2);
                }
                else if (c == 'K'){
                    bool temp1 = s.top();
                    s.pop();
                    bool temp2 = s.top();
                    s.pop();

                    s.push(temp1 & temp2);
                } 
                else if (c == 'E'){
                    bool temp1 = s.top();
                    s.pop();
                    bool temp2 = s.top();
                    s.pop();

                    s.push(temp1 == temp2);
                } 
                else if (c == 'C'){
                    bool temp1 = s.top();
                    s.pop();
                    bool temp2 = s.top();
                    s.pop();

                    s.push(!(temp1 == 1 && temp2 == 0));
                } 
            }
            
            bool ans = s.top(); s.pop();
            if (!ans){
                taut = false;
                break;
            }
        }
        
        if (taut){
            cout << "tautology" << endl;
        }
        else cout << "not" << endl;
    }

    return 0;
}