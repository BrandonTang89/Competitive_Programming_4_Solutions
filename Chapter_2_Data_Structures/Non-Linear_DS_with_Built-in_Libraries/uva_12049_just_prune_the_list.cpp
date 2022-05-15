// UVa 12049 Just Prune the List
// DS Multiset Manipulation
// Time: O(nlog(n) + mlog(m))
// Mem: O(n+m)
// Constraints: n <= 10000, T<100
#include <bits/stdc++.h>
using namespace std;

int n, m, T, temp;
multiset<int> s1, s2;

int main(){
    cin >> T;
    for (int t=0;t<T;t++){
        cin >> n >> m;
        for (int i=0;i<n;i++){
            cin >> temp;
            s1.insert(temp); 
        }
        for (int i=0;i<m;i++){
            cin >> temp;
            s2.insert(temp);
        }

        int ans = 0;
        /*
        Iteratively remove items from s1
            add to count if item not in s2 as well (prune from s1)
            else remove from s2 (not pruned but remove as we have considered item already)
        */

        while(!s1.empty()){
            int cur = *s1.begin();
            auto it = s2.find(cur);
            if (it != s2.end()){
                s1.erase(s1.begin());
                s2.erase(it);
            }
            else{
                ans ++;
                s1.erase(s1.begin());
            }
        }
        
        // Count number of items in s2 left (prune from s2)
        ans += s2.size();
        cout << ans << endl;

        s1.clear();
        s2.clear();
    }

    return 0;
}