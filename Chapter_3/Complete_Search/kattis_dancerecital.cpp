/* Kattis - Dancerecital
This complete search problem is relatively easy in theory but could make one frustrated due to various bugs 
and complex work with bitmasks

Observation 1:
    Since n <= 10, technically a complete search solution should be fast enough, 
    it seems that that is just barely true for this question.

    The super naive version of n! * n * 26^2 operations by checking every 2 adjacent dances with 2 for loops
    obviously doesnt work.

    A simple but better way is to use a bitset to note which of the dancers appear in each adjacent dance and
    compare the adjacent bitsets to find the number of dancers that appear in both.

Observation 2:
    Since we process the dances linearly, we shouldn't have to generate 2 bitsets every time, in fact we should
    just store the bitset for the later dance and use it as that of the earlier dance in the next iteration

Observation 3:
    Since there is only a max of 26 dancers, we should use a bitmask instead of bitset for much more efficient 
    computation.

Observation 4:
    since we are using a bitmask already, checking for common dancers could be done in O(number of common dancers)
    rather than O(26). This is done by taking the bitwise & of both bitmasks and then repeatedly removing the
    least significant binary digit (found using LSOne) and incrementing the number of changes

Observation 4.1:
    There are only n^2 possible adjacent dances but we are currently checking n*n! adjacent dances... meaning we
    should just memorise the number of common dancers between every 2 adjacent dances rather than repeatedly
    recomputing this number in (26 + number of common dancers) operations. However, this observation is not
    needed to attain an AC solution due to the low number of cheap operations required to compute the
    number of common dancers (if implementing the above observations)
    
    thus this observation is not implemented into the code but could be used to further speed up the code or 
    as a replacement for some of the other observations (like not using the LSOne)

Observation 5:
    This is a simple pruning observation. If anywhere along the linear scan of the permutation, the total number
    of changes is already more than our current lowest value, obviously the candidate solution is not going to work
    so we just continue to the next candidate.
s

Debugging 1:
    This is a problem which can result in a really hard to find bug: if we do not sort all the dances initially,
    next_permutation will not run through permutations lexicographically smaller than the initial array...

With the optimisations, we are able to


*/
#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))
int n; // <= 10
string dances[10];

int main(){
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> dances[i];
    }

    sort(dances, dances+n);

    int min_changes = INT_MAX;
    do{
        int changes = 0, dance1 = 0, dance2 = 0; // dance1 comes before dance2

        // Load data for first dance
        for (auto dancer: dances[0]){
            dance2 = dance2 | (1<<(dancer -'A')); 
        }

        for (int i=1;i<n;i++){
            dance1 = dance2;
            dance2 = 0;
            for (auto dancer: dances[i]){
                dance2 = dance2 | (1<<(dancer -'A')); 
            }
            
            int dance_combine = dance1 & dance2;
            while (dance_combine > 0){ // count number of set bits
                dance_combine-=LSOne(dance_combine);
                changes++;
            }

            if (changes > min_changes)break;
        }
        //cout << changes << endl;
        min_changes = min(min_changes, changes);

    }
    while(next_permutation(dances, dances+n));

    cout << min_changes << endl;
    return 0;
}