/* Kattis - Chopwood
This is a prufer sequence problem.. getting the tree as a usable data structure is not needed, it has been included
into the code via the filling up of the parent array

Observation 1:
    there exist a bijection between each prufer sequence and each tree.
    obviously each tree only produces 1 prufer sequence
    Since there exist an inverse algorithm, the prufer sequence generating algorithm is 1-1 and so each prufer sequence
    iis unique to each tree. (ik it sounds handwavy but its legit, just roll with it)

Observation 2:
    if the prufer sequence is not valid in some way, there will not be any available 1 degree vertices to add as our next
    vertex at some point.

    Contrapositive proof:
        if there exist an available vertex to add, we can always continue building the tree as
        the only condition to continue the building algorithm is to get the next lowest value leaf 
        from the priority queue, 
        thus, if theres always an available vertex, we can build a tree
        indicating that the prufer sequence is valid for that tree that we have just constructed

Time: O(n), Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

int n;
int degree[200009], a[200009], parent[200009], ans[200009];
priority_queue<int, vector<int>, greater<int>> d1v; // vertices with degree 1

int main(){
    scanf("%d", &n);
    for (int i=1;i<=n;i++){
        scanf("%d", &a[i]);
        degree[a[i]]++;
        //degree of each node is number of occurences in a+1
    }
    for (int i=1;i<= n+1;i++)degree[i]++;
    for (int i=1;i<=n;i++){
        if (degree[i] == 1)d1v.push(i);
    }

    bool correct = true;
    for (int i=1;i<=n;i++){
        if (d1v.empty()){
            correct = false;
            break;
        }
        parent[d1v.top()] = a[i];
        ans[i] = d1v.top();

        degree[d1v.top()]--; // should become 0
        degree[a[i]]--;

        d1v.pop();
        if (degree[a[i]] == 1){
            d1v.push(a[i]);
        }
    }
    
    for (int i=1;i<=n;i++){
        if (degree[i] != 0){
            correct = false;
            break;
        }
    }

    if (!correct){
        printf("Error\n");
    }
    else{
        for (int i=1;i<=n;i++){
            printf("%d\n", ans[i]);
        }
    }

    return 0;
}