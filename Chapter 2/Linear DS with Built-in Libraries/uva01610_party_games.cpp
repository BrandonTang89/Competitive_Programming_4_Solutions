// UVa 01610 Party Games
// Damn tilting, like legit, the number of edge cases are super annoying
// String and array concepts are simple to understand but hard to implement to deal with all the cases effectively
// Time: O(n log n) for sort per test case, Mem: O(n) for vector

#include <bits/stdc++.h>
using namespace std;

int main(){

    int n;
    
    while (true){
        cin >> n;
        //cout << "----" << endl;
        if (n == 0){
            break;
        }

        vector<string> names;
        for (int i=0;i<n;i++){
            string name;
            cin >> name; 
            names.push_back(name);
        }
        
        sort(names.begin(), names.end());

        /*
        for (auto i:names)cout << i << " ";
        cout << endl;*/

        

        string left_name = names[n/2 -1];
        string right_name = names[n/2];

        string ans = "";

        for (int i=0; i< min(left_name.length(), right_name.length()); i++){
            if (left_name[i] == right_name[i]){
                ans += left_name[i];
            }
            else break;
        }

        if (ans == left_name){
            cout << ans << endl;
            continue; 
        }
        string left_name_full = left_name;
        string right_name_full = right_name;
        left_name.erase(0, ans.length());
        right_name.erase(0, ans.length());

        if (left_name[0] + 1 != right_name[0]){
            if (left_name.length() != 1){
                ans += (left_name[0] + 1);
                cout << ans << endl;
            }
            else
                cout << ans + left_name << endl;
                
            continue;
        }
        
        // left_name[0] == right_name[0];

        if (right_name.length() == 1) {
            ans += left_name[0];
            for (int i=1; left_name_full > ans; i++){
                if (left_name[i] == 'Z')ans += left_name[i];
                else {
                    if (i != left_name.length()-1)
                    ans += left_name[i] + 1;
                    else
                    ans += left_name[i];
                }
            }
            cout << ans << endl;
            continue;
        }
        
        if (left_name.length() == 1){
            ans += (left_name[0]);
        }
        else
            ans += (left_name[0] + 1);
        cout << ans << endl;
 
    }

    return 0;
}