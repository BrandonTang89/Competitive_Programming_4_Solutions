/* Kattis - Monk

Observation 1:
    First we need to prove that there exists a time where the monk is in the same place. Note that we the graph of the 
    height over time for both ascend and descend are continuous and non-decreasing/non-increasing respectively. Since the 
    height of ascend starts at 0 and ends at the mountain height and the height of descend starts at the mountain height
    and ends at 0, there must be an intersection at a unique height (though not necessrily unique time since the monk
    could rest at the intersection height on both ascend and descend at the same time of the day).

Observation 2:
    clearly this is a problem of finding the intersection between 2 functions that are non-decreasing/non-increasing..
    Note that given a candidate time, we can calculate the position in both the ascend and descend climbes. if the monk is
    higher in the ascend than the descend at this time, we have past the intersection. Conversely, if the monk is lower in the
    ascend than the descend, then we have not reached the inersection point. Using this, we can binary search for the answer.

Observation 3:
    How do we know how much to binary search? We just note that the search space is at most 500000 / (2**t)
    for t iterations of binary search. Solving for 500000 / (2**t) < 1e-5, we get t > 35.54 from wolfram alpha.
    So we just choose ceil(35.54) = 36. 
    But if this math stuff is not for you, just binary search the grader, if t is too small, it will WA, if t is too
    big, it will TLE... at an interval in between, we get AC!

Time: O(36 * (a+d)), Mem: O(a+d)
*/
#include <bits/stdc++.h>
using namespace std;

int a, d; // ascend, decend
int h, t; // height time
double r, l, m, mt_h, mt_t; // binary search variables, right left mid, mountain height and time (to ascend)
double tl, ascend_height, descend_height; // simulation variables
pair<int,int> rising[5001], falling[5001]; // (height, time)
int main(){
    cin >> a >> d;
    mt_h = 0;
    for (int i=0;i<a;i++){
        cin >> h >> t;
        rising[i] = make_pair(h,t);
        mt_h += h;
        mt_t += t;
    }
    for (int i=0;i<d;i++){
        cin >> h >> t;
        falling[i] = make_pair(h,t);
    }

    // BSTA for intersection point, try different time values
    l = 0, r = mt_t;
    
    for (int i=0;i<36;i++){
        m = (r+l)/2;
        // compute ascend height
        ascend_height = 0;
        tl = m; // time_left;
        for (int seg=0;; seg++){
            if (rising[seg].second < tl){
                ascend_height += rising[seg].first;
                tl -= rising[seg].second;
            }
            else{
                ascend_height += (rising[seg].first  * tl / rising[seg].second);
                tl = 0;
                break;
            }
        }

        // compute descend height
        descend_height = mt_h;
        tl = m;
        for (int seg=0;descend_height>0;seg++){ 
            // note that if the time selected is greater than the total descend time, we need to break early
            if (falling[seg].second < tl){
                descend_height -= falling[seg].first;
                tl -= falling[seg].second;
            }
            else{
                descend_height -= (falling[seg].first  * tl / falling[seg].second);
                tl = 0;
                break;
            }
        }

        if (descend_height > ascend_height){// too early
            l = m;
        }
        else{
            r = m;
        }
    }

    cout << l << endl;
    
    return 0;
}