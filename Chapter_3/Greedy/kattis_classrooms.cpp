/* Kattis - classrooms
Observation 0:
    Since n,k <= 200000, we can guess that a O(n log k) solution is expected... so some sort of linear pass of 
    activities with log k cost per activity, thus indicating that binary search could be involved.
Observation 1:
    Consider the subtask k=1: It should be decently intuitive that we should process the activities in ascending
    ending time, the order of activites with the same ending time but different starting time doesn't matter.
    Doing this ensures that we always select to use activities with the earliest ending times so that we can
    fit the next activity after that with as much remaining space as possible.
Observation 2: 
    Given the k classrooms, we should still process the activities in increasing ending time. However... which
    classroom do we assign activities to? Well intuitively, we should try to assign each activity to the classroom
    with the latest available time that can still fit the new activity. This is because it will allow other classrooms
    with earlier available times to accomdate bigger activites with later ending times that we may not have processed yet.

    Implementation wise, we can store the next available times of each classroom in a multiset to allow for log k finding 
    of the latest available time that an activity can still be included.

These observations might not be rigourous but they convinced me that the greedy approach is likely correct.

Debugging:
    Use ms.lower_bound instead of the lower_bound function. The latter should only be used for vectors or arrays with
    random access iterators, else it will be O(k) instead of O(log k) complexity.

Time: O(n log k), Mem: O(n + k)
*/
#include <bits/stdc++.h>
using namespace std;

int n, k, s, f;
vector<pair<int,int>> v;
multiset<int> ms;
int main(){
    scanf("%d %d", &n, &k);
    for (int i=0;i<n;i++){
        scanf("%d %d", &s, &f);
        v.emplace_back(make_pair(f, s));
    }
    
    sort(v.begin(), v.end());
    for (int i=0;i<k;i++)ms.insert(0);

    int counter = 0;
    for (auto a:v){
        f = a.first;
        s = a.second;

        //printf("considering activity: %d %d\n", s, f);
        auto it = ms.upper_bound(-s);
        if (it == ms.end())continue; // cannot fit this activity

        ms.insert(-f);
        ms.erase(it);
        counter++;
    }

    printf("%d\n", counter);
    return 0;
}