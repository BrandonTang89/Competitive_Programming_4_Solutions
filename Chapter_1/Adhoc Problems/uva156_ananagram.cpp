// UVa 156 Ananagram
// Relatively simple question to check if a word has no anagrams within a given dictionary of size n
// Time: O(n^2) as count is linear in number of matches ie if every element in the dictionary are anagrams of each other this will take forever
// Mem: O(n) sorted strings stored in multiset
// Constraints: n <= 1000 so technically n^3 could have passed too
#include <bits/stdc++.h>
using namespace std;

multiset<string> m;

string sort_string(string s){
    string s_lower = "";
    for (auto c:s){
        s_lower += tolower(c);
    }

    sort(s_lower.begin(), s_lower.end());
    return s_lower;
}

int main(){
    string word;
    vector<string> words;
    while (true){
        cin >> word;
        if (word == "#")break;

        m.insert(sort_string(word));
        words.push_back(word);
    }

    sort(words.begin(), words.end());
    for (auto word: words){
        if (m.count(sort_string(word)) == 1){
            cout << word << endl;
        }
    }


    return 0;
}