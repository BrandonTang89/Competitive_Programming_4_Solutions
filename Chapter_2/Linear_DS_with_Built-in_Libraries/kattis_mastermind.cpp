// Kattis mastermind - Mastering Mastermind
// a basic 1d array problem that is made easier with the use of sets
// Time: O(n^2), Mem: O(n)
/*

note that a Time: O(n log n) solution could be made by 

    creating a map of pair<char, no_occurances> for guess, code_colours
    for each i in code_colours:
        binary search to attain no_occurances for guess and code_colours since map stores the pair values in sorted order
        s += min(guess_num, code_num)    

However ths is overkill for the N<50 task limits
*/
#include <bits/stdc++.h>
using namespace std;

char code[59], guess[59];
int n,r=0,s=0;

set<char> code_colours;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i=0;i<n;i++)cin>>code[i];
    for (int i=0;i<n;i++)cin >> guess[i];

    for (int i=0;i<n;i++){
        if(code[i]== guess[i])r++;
        code_colours.insert(code[i]);
    }
    
    for (auto i: code_colours){
        //cout << i << endl;
        int guess_num = 0, code_num = 0;
        for (int j=0;j<n; j++){
            if (i == guess[j]){
                guess_num++;
            }
            if (i == code[j]){
                code_num++;
            }
        }
        s += min(guess_num, code_num);
    }

    s -= r;
    cout << r << " " << s << endl;

    return 0;
}