/* Kattis - GCPC
A somewhat introductory question to the order statistics tree. Using policy based data structures with key type
as a tuple of 3 ints makes the question decently easy. Note how we negate some of the ints to sort them ascendingly

Note that order statistic tree has log n rank/select methods
Time: O(m log n) Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree<tuple<long long,long long,long long>, null_type, greater<tuple<long long,long long,long long>>, rb_tree_tag,
             tree_order_statistics_node_update> ost;

// tree stores (problems_scored, -penalty, -team_number)
long long n, m, t, p;
pair<long long,long long> arr[100000 + 9]; // arr[team_number] = (problems_scored, penalty)
int main(){
    cin >> n >> m;
    ost tree;
    for (int i=1;i<=n;i++){
        arr[i] = make_pair(0,0);
        tree.insert(make_tuple(0,0,-i));
    }

    for (int e=0;e<m;e++){
        cin >> t >> p;
        tree.erase(make_tuple(arr[t].first, -arr[t].second, -t));
        arr[t] = make_pair(arr[t].first+1, arr[t].second+p);
        tree.insert(make_tuple(arr[t].first, -arr[t].second, -t));

        cout << tree.order_of_key(make_tuple(arr[1].first, -arr[1].second, -1))+1 << endl;

    }
}