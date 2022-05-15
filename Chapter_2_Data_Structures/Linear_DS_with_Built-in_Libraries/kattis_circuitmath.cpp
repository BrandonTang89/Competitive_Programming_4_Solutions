/*
Kattis - Circuitmath
A basic post fix calculator with bitwise operations on boolean values. Easily implemented with a stack

Time: O(number of operations + n), Mem: O(n);
*/ 
#include <bits/stdc++.h>
using namespace std;

bool vals[26];
int n;
stack<bool> s;
int main(){
    cin >> n;
    char temp;
    for (int i=0;i<n;i++){
        cin >> temp;
        if (temp == 'T'){
            vals[i] = true;
        }
        else vals[i] = false;
    }

    bool a, b;
    while (cin >> temp){
        if (temp == '*'){
            a = s.top(); s.pop();
            b = s.top(); s.pop();
            //printf("pushing %d\n",a&b);
            s.push(a&b);
        }
        else if (temp == '+'){
            a = s.top(); s.pop();
            b = s.top(); s.pop();
            //printf("pushing %d\n",a|b);
            s.push(a|b);
        }
        else if (temp == '-'){
            a = s.top(); s.pop();
            //printf("pushing %d\n",!a);
            s.push(!a);
        }
        else s.push(vals[temp-'A']);
    }

    a = s.top();
    if (a){
        cout << "T" << endl;
    }
    else cout << "F" << endl;
    
}