/* UVa 11581 Grid Successors
A question that requires some reading comprehension skills. Simulate the process and record the states that have been computed before and check for new states.
A solution I implemented with set<bitset<9>> didn't work probably because set cannot compare 2 bitset values thus i used an inefficient vector
Time: O(TC * N^2) where N is the number of states checked before repetition is found. Can be improved to O(TC * n log n) by using set of bitmasks. f() would also be alot faster that way
Memory: O(N)
*/
#include <bits/stdc++.h>
using namespace std;

bitset<9> f(bitset<9> g){
    bitset<9> fg;
    fg[0] = (g[1]^g[3]);
    fg[1] = (g[0] + g[2] + g[4])%2;
    fg[2] = g[1]^g[5];
    fg[3] = (g[0] + g[4] + g[6])%2;
    fg[4] = (g[1] + g[3] + g[5] + g[7])%2;
    fg[5] = (g[4] + g[2] + g[8])%2;
    fg[6] = (g[3] + g[7])%2;
    fg[7] = (g[6] + g[4] + g[8])%2;
    fg[8] = (g[5] + g[7])%2;

    /*
    cout << "--" << endl;
    cout << fg[0] << fg[1] << fg[2] << endl;
    cout << fg[3] << fg[4] << fg[5] << endl;
    cout << fg[6] << fg[7] << fg[8] << endl;
    */

    return(fg);
}

vector<bitset<9>> s;
bitset<9> g;
bitset<9> new_g;

int T;
int main(){
    cin >> T;
    
    for (int t=0; t<T; t++){
        string temp;
        
        cin>>temp;

        g[0] = temp[0]-'0'; g[1]=temp[1]-'0'; g[2]=temp[2]-'0';
        cin>>temp;
        g[3] = temp[0]-'0'; g[4]=temp[1]-'0'; g[5]=temp[2]-'0';
        cin>>temp;
        g[6] = temp[0]-'0'; g[7]=temp[1]-'0'; g[8]=temp[2]-'0';

        
        s.push_back(g);
        
        
        int count = 0;
        while (true){
            new_g = f(g);
            //cout << new_g << endl;
            if (find(s.begin(), s.end(), new_g) != s.end()){
                break;
            }
            s.push_back(new_g);
            g = new_g;
            count++;
        }

        cout << count -1 << endl;

        s.clear();
        
        
    }



    return 0;
}