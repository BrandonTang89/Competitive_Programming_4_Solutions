/* Kattis - Sim
This seems like an introductory question to lists, not that lists are often used in ICPC style contests anyway
Just follow the instructions and use some common sense. 
    Also beware of invalid pointers for when u backspace at the front of the list.
    Also remember to clear list between testcases

Time: O(length of string * T), Mem: O(length of string)
*/
#include <bits/stdc++.h>
using namespace std;

int T;
list<char> l;
string line;
int main(){
    cin >> T;
    cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); // clear the \n from the input buffer before using getline
    for (int tc=0;tc<T;tc++){
        getline(cin,line);
        
        list<char>::iterator it = l.begin();
        for (int p=0;p<line.length();p++){
            //cout << p << endl;
            if (line[p] == ']'){
                it = l.end();
            }
            else if (line[p] == '['){
                it = l.begin();
            }
            else if (line[p] == '<'){
                list<char>::iterator temp = it;
                temp--;
                if (temp == --l.begin())continue;
                l.erase(temp);
            }
            else{
                l.insert(it, line[p]);
            }
            //for(auto i: l){cout << i;}cout << endl;
        }
        for(auto i: l){cout << i;}cout << endl;
        l.clear();
        
    }
    
    return 0;
}