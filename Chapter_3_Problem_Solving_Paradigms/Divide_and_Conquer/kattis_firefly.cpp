/* Kattis - Firefly

Observation 1:
    Since we are interested in the number of hits in the run, the relatively order of obstacles doesn't matter.
    This means we can assuming that all staglamites come before stalacites and all obstacles of each type are 
    in increasing height, allowing us to see the insight better.

    Specifically, if the obstacles are sorted, we can use binary search to find their relative position in their
    arrays to determine the number of obstacles the firefly can fly over and thus the number of obstacles
    the firefly will have to fly through


Time: O(h log n), Mem: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

int n, h;
int rising[200010], falling[200010]; // stalagmites and stalacites
int main(){
    cin >> n >> h;
    for (int i=0;i<n;i++){
        if (i & 1){ // i is odd
            cin >> falling[i/2];
        }
        else cin >> rising[i/2];
    }

    sort(rising, rising+n/2);
    sort(falling, falling+n/2);

    int num_rising, num_falling; // number of obstacles that firefly can fly over/under
    int num_hits;
    int min_hits=INT_MAX, count=0;
    for (int ch=1;ch<=h;ch++){ // ch between 1 and h since cannot fly in the floor or ceiling
        num_rising = lower_bound(rising, rising+n/2, ch) - rising;
        num_falling = lower_bound(falling, falling+n/2, h-ch+1) - falling;

        //printf("ch: %d, num rising: %d, num falling: %d\n", ch, num_rising, num_falling);
        num_hits = n - num_falling - num_rising;
        if (num_hits < min_hits){
            min_hits = num_hits;
            count = 1;
        }
        else if (num_hits == min_hits){
            count++;
        }
    }

    cout << min_hits << " " << count << endl;

    return 0;
}