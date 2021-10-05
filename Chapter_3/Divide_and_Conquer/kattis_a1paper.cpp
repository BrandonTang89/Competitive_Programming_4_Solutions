/* Kattis - a1paper
Honestly feels more like an adhoc than a divide and conquer question.

Naive Approach:
    Use a recursive function to generate an A1 paper, calling itself twice to create 2 of the next step smaller papers
    if needed.

    O(2^n), this is not practical.

Observation 1:
    From looking at the naive approach, we notice that we can just collate all the required number of each paper size
    As we progress from 1 paper to another. We do this by adding a "quantity" parameter to our function. We try to take
    as many papers already made of the target size, if we do not have enough, we make 2 times the number of smaller papers
    as we need of the target paper. This way, each node in the recursion tree only has 1 child instead of 2.
    
    This results in linear complexity instead of exponential!

Debugging 1:
    when printing floats with c++, use std::cout << std::setprecision(10); for higher precision output of floating point
    numbers

Time: O(n), Mem: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

int n;
int papers[33]; // papers[i] = number of Ai papers left, papers[0] = papers[1] = 0;
long double long_sides[33];
bool possible = true;

double cost_for(int target, int q){ // target paper size, q quantity
    //printf("target: %d, quantity: %d\n", target, q);
    if (target > n){ // need a paper smaller than whatever minimum he has
        possible = false;
        return 0;
    }

    if (papers[target] >= q){ //get grab the paper if possible
        return 0;
    }
    if (papers[target] > 0){
        q-= papers[target]; // just take all the available papers first
    }

    // else make the paper
    return (cost_for(target+1, q*2) + q*long_sides[target+1]);
}
int main(){
    cin >> n;
    long_sides[1] = 0.8408964152537146;
    const long double sqrt2 = sqrt(2);
    for (int i=2;i<=n;i++){
        cin >> papers[i];
        long_sides[i] = long_sides[i-1]/sqrt2;
    }

    long double cost = cost_for(1, 1); // cost to make an A1 paper
    if (possible){
        std::cout << std::setprecision(10);
        cout << cost << endl;
    }
    else{
        cout << "impossible" << endl;
    }


    return 0;
}