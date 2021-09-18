/* UVA 10145 Lock Manager
Use unordered map and set to make a lock manager
Time per test case: O(n) approx assuming O(1) operations for all hashtable methods
Mem: O(n)

*/

#include <bits/stdc++.h>
using namespace std;

int T;
unordered_set<int> blocked_trids;
unordered_map<int, pair<bool, int>> m;

int main(){
    cin >> T;
    for (int testcase =0; testcase< T; testcase++){
        char mode;
        int trid, item; 
        blocked_trids.clear();
        m.clear();
        while(true){
            cin >> mode;
            if (mode == '#')break;
            cin >> trid >> item; 

            // cout << "REQ: " << mode << " " << trid << " " << item << endl;
            if  (blocked_trids.find(trid) != blocked_trids.end()){
                cout << "IGNORED" << endl;
            }
            else{ // TRID not blocked
                if (m.find(item) == m.end()){ // New Item
                    //cout << "item " << item << endl;
                    cout << "GRANTED" << endl;
                    m[item] = make_pair(mode == 'X', trid);
                }
                else if (mode == 'S'){ // S Mode and Old Item
                    
                    if (m[item].first == false){
                        if (m[item].second != trid)
                            m[item].second = -1; // if there are more than 1 'S' request for the item, the next 'X' will be blocked
                        cout << "GRANTED" << endl;
                    }
                    else{
                        if (trid != m[item].second){
                            cout << "DENIED" << endl;
                            blocked_trids.insert(trid);
                        }
                        else{
                            cout << "GRANTED" << endl;
                        }
                    }
                }
                else{ // MODE == 'X' and Old Item
                    //cout << "Trid " << trid << " m second " << m[item].second << endl;
                    if (trid !=  m[item].second){ // Check to block
                        cout << "DENIED" << endl;
                        blocked_trids.insert(trid);
                    }
                    else{ // grant, update m
                        cout << "GRANTED" << endl;
                        m[item] = make_pair(true, trid);
                    }
                }
            }
        }

        if (testcase != T-1)
            cout << endl;
    }
    return 0;
}