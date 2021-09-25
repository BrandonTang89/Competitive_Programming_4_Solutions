/*
Kattis - Compound Words
Very easy problem with sets.

Time: O(n^2 log n), Mem: O(n^2)
*/ 
#include <bits/stdc++.h>
using namespace std;

set<string> cws; // compound words
vector<string> v; // initial words
string w;
int main(){
    while (cin >> w){
        v.emplace_back(w);
    }
    
    for (auto i: v){
        for (auto j:v){
            if (i==j)continue;
            cws.insert(i+j);
        }
    }
    for (auto i:cws){
        cout << i << endl;
    }

    return 0;
}