// UVA 10887 Concatenation of Languages
// Relatively simple set based problem to remove duplicate concatenated words. Have to deal with the annoying edge case of the empty string as a word...
// Time: O(NM + NM log NM), Mem: O(NM)
#include <bits/stdc++.h>
using namespace std;

string lan_1[1509];
string lan_2[1509];

unordered_set<string> concat_words;

int T, n, m;
string temp;

int main(){
    cin >> T;
    for (int tc=0; tc<T; tc++){
        cin >> n >> m;
        cin.ignore(256, '\n'); 
        for (int i=0;i<n;i++){
             getline(cin, lan_1[i]);
        }
        for (int i=0;i<m;i++){
            getline(cin, lan_2[i]);
        }

        for (int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                //cout << "nw : " << lan_1[i] + lan_2[j] << endl;
                concat_words.insert(lan_1[i] + lan_2[j]);
            }
        }

        cout << "Case " << tc+1 << ": " << concat_words.size() << endl;
        concat_words.clear();
    }
}