/* Kattis - Knigsoftheforest
A relatively basic question on the use of priority queue. Just beware of the edge case where karl joins in 2011
and you should be good to go :)

Time: O((n+k) log (n+k)) for the sorting by year, the actual processing is O(n log k) due to n years, log k insert into pq
Mem: O(n+k)
*/
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<pair<int,int>> contenders; // (year, strength)
priority_queue<pair<int, bool>> pq; // (strength, is karl?)

int main(){
    cin >> k >> n;
    pair<int, int> karl;
    int year, strength;

    cin >> year >> strength;
    year -= 2011;
    karl = make_pair(year, strength);

    bool karl_in = false;
    if (karl.first == 0){
        pq.push(make_pair(karl.second, true));
        karl_in = true;
    }

    for (int i=0;i<(n+k-2);i++){
        cin >> year >> strength;
        contenders.push_back(make_pair(year-2011,strength));
    }
    sort(contenders.begin(), contenders.end());
    
    int index=0;
    for(;contenders[index].first==0; index++){
        //printf("Pushing moose with strength: %d\n", contenders[index].second);
        pq.push(make_pair(contenders[index].second, false));
    }

    bool won = false;
    for(int i=0;i<n;i++){ // year i
        pair<int,int> winner = pq.top();
        pq.pop();

        if (winner.second){
            cout << i+2011 << endl;
            won = true;
            break;
        }

        //printf("i: %d\n", i);

        if (i+1 == karl.first && !karl_in){
            //printf("Pushing karl\n");
            pq.push(make_pair(karl.second, true));
            karl_in = true;
        }
        else if (i!=n-1){
            //printf("Pushing moose with strength: %d\n", contenders[index].second);
            pq.push(make_pair(contenders[index].second, false));
            index++;
        }
    }
    if (!won)cout << "unknown\n";

    return 0;
}