/* Kattis - goingtoseed
My first interactive question since before NOI 2019 (insert another clown emoji)...

Observation 1: 
    Obviously the question is a binary search variant... Given this, we know the solution space after 16 iterations is
    at most 1e9/x^16 where x is how many regions we split the search area into (assuming we can determine which)
    region the target is in in 1 query. Solving for x, we realise x must be at least 4. This is actually consistent with
    the fact that we get 2 bits of data per query, ie max of 4 possible answers... 

    So how do we design the ranges then? After some thinking, note that if we make the size of each range to half the 
    search space and start the first range at the begining of the search area while the second range starts at 
    25% of the search area, ie {l1 --- l2 --- r1 --- r2 --- }, we can make full use of the data, where {01, 11, 10, 00}
    corresponds to each of the 4 25% regions represented by ---.

However, the most annoying part about this problem is the implementation details: like with +1 -1 or whatever when 
modifying the search area after each query, and dealing with the end of the search when the search space is small 
(<= 4). Also it is difficult to debug due to its interactive nature.. one could write another grader program to help
but that seems to take too long :(

Time: (log(n))
Mem: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

int low, high, n; 
int main(){
    cin >> n;
    high = n;
    low = 1;
    
    int l1, r1, l2, r2;
    int a, b;
    while (high - low + 1 > 3){ // query
        //printf("low: %d, high: %d\n", low, high);
        l1 = low;
        r1 = low + (int)(high - low + 1) * 0.5-1;
        l2 = low + (int)(high - low + 1) * 0.25;
        r2 = low + (int)(high - low + 1) * 0.75-1;

        cout << "Q " << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
        cout.flush();

        cin >> a >> b;
        if (a == 1 && b == 0){ // first quarter
            high = l2;
            if (l2 - l1 <= 1){
                cout << "A " << l1 << endl;
                return 0;
            }
        }
        else if (a == 1 && b == 1){
            low = l2 - 1;
            high = r1 + 1;
            if (l2 == r1){
                cout << "A " << r1 << endl;
                return 0;
            }
        }
        else if (a == 0 && b == 1){
            low = r1;
            high = r2+1;
            if (r2 - r1 <= 1){
                cout << "A " << r2 << endl;
                return 0;
            }
        }
        else{
            low = r2;
            high = min(high+1, n);
            if (high - r2 == 1){
                cout << "A " << high << endl;
                return 0;
            }
        }
    }
    //printf("last 3: low: %d, high: %d\n", low, high);
    cout << "Q " << low << " " << low << " " << low+1 << " " << low+1 << endl;
    cout.flush();
    cin >> a >> b;
    if (a == 1 && b == 0){
        high = low;
    }
    else if (a == 0 && b == 1){
        high = low+1;
    }
    else{
        high = high; 
    }

    cout << "A " << high << endl;

    return 0;
}