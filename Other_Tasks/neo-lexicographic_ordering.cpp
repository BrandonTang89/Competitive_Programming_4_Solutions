/*
Abridge Problem Statement: given a new alphabetical order, sort n strings lexicographically
input format:
    new_order (string of lowercase letters)
    n (int 1<=n<=50000)
    s1 (string)
    s2 (string)
    .
    .
    .
    sn (string)

Output format:
    s1
    s2
    .
    .
    .
    sn
    where the strings are sorted lexicographically

Solution: Use a custom comparision sort function together with a map to easily compare the relative ordering of chars
*/

#include <bits/stdc++.h>
using namespace std;

map<char, int> m; //m[char] == position in the new order

bool compare(string s1, string s2){
    for (int i=0;i<min(s1.length(), s2.length()); i++){
        if (m[s1[i]] < m[s2[i]])return true;
        if (m[s1[i]] > m[s2[i]])return false;
    }

    return (s1.length() < s2.length());
}

string new_order;
int n;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> new_order >> n;
    for (int i=0;i<26;i++)m[new_order[i]] = i;

    string vs[50009];
    for (int i=0;i<n;i++){
        cin>> vs[i];
    }
    sort(vs, vs+n, compare);

    for(int i=0;i<n;i++){
        cout << vs[i] << endl;
    }

    return 0;
}