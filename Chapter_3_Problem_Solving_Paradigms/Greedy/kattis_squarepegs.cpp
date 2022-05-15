/* Kattis - Squarepegs

Observation 1:
    We can just convert all square houses into their respective circular house such that the square house is inscribed in
    the circular house. For this, we use the pythagorean theorem to note that r = s/sqrt(2) where r is the radius of the
    circular house and s is the side of the square house.

Observation 2;
    This is now just a greedy matching problem where we try to fit the houses in ascending size, for each house we put it
    into the smallest plot that can fit it. 

Time: O((m+k) log (m+k) + n log n), longest part is the sorting
Mem: O(n + m + k)
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, k, r, s;
const double sqrt2 = sqrt(2);
vector<double> plots;
vector<double> circle_houses;
int main(){
    cin >> n >> m >> k; // plots, circle house, square house
    for (int i=0;i<n;i++){
        cin >> r;
        plots.emplace_back(r);
    }
    for (int i=0;i<m;i++){
        cin >> r;
        circle_houses.emplace_back(r);
    }
    for (int i=0;i<k;i++){
        cin >> s;
        s = s/sqrt2;
        circle_houses.emplace_back(s);
    }
    sort(plots.begin(), plots.end());
    sort(circle_houses.begin(), circle_houses.end());

    int counter=0;
    int house=0, plot=0;
    while ((house < m+k) && (plot<n)){ // greedily put the task into the smallest interval that can fit it
        //printf("plot: %d, house: %d\n", plot, house);
        while ((plots[plot] <= circle_houses[house]) && (plot<n)){ // task takes more time than current interval
            plot++;
        }
        if (plot == n)break;
        // Assign this task to this interval
        counter++;
        house++;
        plot++;
    }
    cout << counter << endl;


    return 0;
}