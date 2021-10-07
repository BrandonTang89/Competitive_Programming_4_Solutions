/* Kattis - froshweek2

Observation 1:
    It should be obvious that we will be able to fit the most number of tasks if we fit all the tasks in ascending 
    time taken so we fit as small of tasks as possible.
Observation 2:
    Now, to ensure as little "time wastage", it should also make sense that we assign the smallest task to the smallest
    interval that can still fit the task.. After that we can ignore all intervals smallest than that interval (and that
    interval itself). We can also ignore the smallest task. Now, we repeated that for all tasks until there are no more
    tasks or no more intervals.

    This greedy solution is optimal.

Time: O(n + m), Mem: O(n + m)
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, l;
vector<int> tasks, intervals;
int main(){
    cin >> n >> m;
    for (int i=0;i<n;i++){
        cin >> l;
        tasks.emplace_back(l);
    }
    for (int i=0;i<m;i++){
        cin >> l;
        intervals.emplace_back(l);
    }

    sort(tasks.begin(), tasks.end());
    sort(intervals.begin(), intervals.end());

    int t=0, in=0;
    int counter=0;
    while ((t<n) && (in<m)){ // greedily put the task into the smallest interval that can fit it
        while ((tasks[t] > intervals[in]) && (in<m)){ // task takes more time than current interval
            in++;
        }
        if (in == m)break;
        // Assign this task to this interval
        counter++;
        t++;
        in++;
    }

    cout << counter << endl;
    return 0;
}