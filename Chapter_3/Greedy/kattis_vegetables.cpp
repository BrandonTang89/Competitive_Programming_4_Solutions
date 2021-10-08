/* Kattis - vegetables
This question took me way too long to figure out.

Observation 1:
    Consider an optimal solution. Now in this optimal solution, we consider each initial vegetable as being cut into
    1 or more slices (number of cuts + 1). note that it is always not worse to choose the cuts such that the slices
    are of equal length.

    Proof:
        if the slices are not of equal length, there must be a minimum length. If this is the global minimum length slice
        then equalizing the slices increases this minimum length, thus resulting in a higher ratio, improving t. If it is
        not the global minimum, increasing its length will not affect the ratio.

        if the slices are not of equal length, there must also be a maximum length. If this is the global maximum length,
        then decreasing it by equalising the slices will result in a larger ratio. Else there is no effect on the ratio.

        In any situation, it is always not worse to equalise the lengths of the slices on the vegetable.

Observation 2:
    Now that we know how to arrange the cuts on the vegetables, the optimal solution can be determined by determining
    the number of cuts on each vegetable. 
    
    We note that adding cuts to a vegetable which has a slice length that is not
    the global maximum will never increase the ratio. In fact, the only way to increase the ratio is to increase
    the number of cuts on the vegetable with a slice length that is the global maximum.

    Assume some set of additions of X cuts to an atbitary state results in the optimal solution. 
    We note that somewhere in that set, we must increase the number of cuts on the vegetable with the 
    global maximum current slice length. Since the order in which we increase the cuts is independent to 
    the correctness of the solution, we can choose to do that cut first. Doing so, we a
    rrive at a state that requires X-1 cuts to optimally get the ratio above t.
    
    Repeating the process allows us to get to the optimal division of cuts to get the ratio above t.

Time: O((number of cuts + n) log n) 
Mem: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

priority_queue<tuple<double, int, int>> pq; // current slice, total weight, number of cuts
int n;
double t, w, min_w = INT_MAX;
int main(){
    cin >> t>> n;
    for (int i=0;i<n;i++){
        cin >> w;
        pq.push(make_tuple(w, w, 0));
        min_w = min(min_w, w);
    }

    double ratio = 0;
    int counter = 0;
    while (true){
        auto [cs, tw, nc] = pq.top();
        //printf("cs: %f, tw: %d, nc: %d\n", cs, tw, nc);
        pq.pop();

        if (min_w / cs > t)break;

        nc++;
        cs = tw / (double) (nc+1);
        min_w = min(min_w, cs);
        pq.push(make_tuple(cs, tw, nc));
        counter++;
    }

    cout << counter<< endl;

    return 0;
}