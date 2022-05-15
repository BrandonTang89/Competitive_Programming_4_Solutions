/* Kattis - ceiling

Help my brain hurts... All for 2.2 difficulty points (insert clown emoji)

Observation 1:
    Only the relatively value of the elements matter, so to make the later tree equality comparisions easier,
    we just replace each element by their rank where the smallest element is rank 0. This is done using an auxillary
    sorted array

Observation 2:
    How to represent items in a BST? How to insert elements? idk man, never took a data structures class...
    {edit: we can apparently use pointers.. but nawh lazy}

    How I decided to do it is to represent the tree as a vector of pairs<int,int>, children[tree], where children[tree][node]
    = (left_child, right_child). Then to insert, we start from the root and check its children. we do that until we 
    reach a node which we can insert the new node into.

    When we compare BSTs, just simply use "=" to compare the contents of children[i] and children[j] to compare trees
    i and j.

Time: O(n * k^2 + n^2)
Mem: O(nk)

*/
#include <bits/stdc++.h>
using namespace std;

int n, k;
int arr[21];
int sorted_arr[21];
vector<vector<pair<int,int>>>children;
int main(){
    cin >> n >> k;
    for (int ce=0;ce<n;ce++){ // ceiling
        // first we parse input and make the values distinct but within [0, k-1]
        for (int i=0;i<k;i++){
            cin >> arr[i];
            sorted_arr[i] = arr[i];
        }
        sort(sorted_arr, sorted_arr+k); // sort
        //for (int i=0;i<k;i++)cout << sorted_arr[i] << " "; cout << endl;
        for (int i=0;i<k;i++){
            arr[i] = lower_bound(sorted_arr, sorted_arr+k, arr[i]) - sorted_arr;
            //cout << arr[i] << " ";
        }//cout << endl;
        
        // Make a temp empty vector that is used to expand children
        vector<pair<int,int>> temp;
        children.push_back(temp);
        children[ce].assign(k, make_pair(-1, -1));

        int root = arr[0]; //first element is the root vertex
        int cur_node;
        for(int i=1;i<k;i++){ // for each remaining element
            
            cur_node = root;
            while(true){ // insert into the BST
                if (arr[i] < cur_node){
                    if (children[ce][cur_node].first == -1){ //left subtree empty, we can place i there
                        children[ce][cur_node].first = arr[i];
                        break;
                    }
                    else{
                        cur_node = children[ce][cur_node].first;
                    }
                }
                else{ //arr[i] > arr[cur_node] since unique values
                    if (children[ce][cur_node].second == -1){ //left subtree empty, we can place i there
                        children[ce][cur_node].second = arr[i];
                        break;
                    }
                    else{
                        cur_node = children[ce][cur_node].second;
                    }
                }
            }
        }

        //for (int i=0;i<k;i++){printf("(%d,%d) ", children[ce][i].first, children[ce][i].second);}cout << endl;
        
    }
    
    int unique_count = 0;
    bool unique = true;
    for (int i=0;i<n;i++){
        unique = true;
        for (int j=0;j<i;j++){
            if (children[i] == children[j]){
                // not unque to all that came before
                unique = false;
                break;
            }
        }
        if(unique)unique_count++;
    }

    cout << unique_count << endl;    
}
