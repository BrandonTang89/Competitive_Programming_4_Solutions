/* Kattis - zagrade

Idea 1:
    Obviously this a problem involving the enumeration of all subsets of the valid brackets. However,
    we need to do some pre-processing of the data beforehand, doing a linear scan with a stack to establish the
    location of the bracket pairs which we then store in a vector of pairs.

    We can then use a bitmask, checking at each iteration that indices to not include in the answer

Let the number of bracket pairs be b, the length of the initial sequence be n
Time: O(2^b * (b log b + n)), Mem: O(n * 2^b)
*/
#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))

stack <int> s;
string init;
vector<pair<int,int>>brackets;
int main(){
    cin >> init;

    // load the braket arr
    for (int i=0;i<init.length();i++){
        if (init[i] == '('){
            s.push(i);
        }
        else if (init[i] == ')'){
            brackets.emplace_back(make_pair(s.top(), i));
            s.pop();
        }
    }

    /*
    for (auto i:brackets){
        printf("%d %d\n", i.first, i.second);
    }*/

    int total_b = brackets.size();
    set<string> ans_v;
    for (int bm=1;bm<(1<<total_b); bm++){
        //cout << bm << endl;
        string ans = "";

        unordered_set<int> removed_indices;
        int tbm = bm;
        while (tbm>0){
            int a = LSOne(tbm);
            tbm-= a;
            a = __builtin_ctz(a);
            removed_indices.insert(brackets[a].first);
            removed_indices.insert(brackets[a].second);
        }

        for (int i=0;i<init.length();i++){
            if (removed_indices.find(i) != removed_indices.end())continue;
            ans += init[i];
        }

        ans_v.insert(ans);
    }

    for (auto i: ans_v){
        cout << i << endl;
    }


    return 0;
}