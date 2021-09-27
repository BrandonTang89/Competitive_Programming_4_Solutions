/* Kattis - Babynames

Observation 0:
    The query on this question could be very scary to some (me). 
    However, we need to note that while it is not easy to iterate on strings
    (since aaaaaa...aaaaaa < b), it is easy to compare strings with just the built in < and > relations

Observation 1:
    Thus to get the strings within the interval, we just need to get all strings >= start and < end.
    Since we just want to get the number of strings in this interval, we can make use of the rank function
    which essentially returns the number of strings less than a certain query string

    Specifically, we use the query strings
    largest string <= start (s1)
    largest string <= end (s2)
    
    and calculate the number of strings in the interval with rank[s2]-rank[s1]

Observation 2:
    to get s1 and s2, we can just use the built in lower_bound method with O(log n) complexity with binary search

Observation 3:
    Since there's males and females, we should just use 2 seperate order statistic trees rather than trying hard
    to implement a more complex combined version

Note that more concise code could be written by passing the ost by reference... but meh

Time: O(q log n), Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree<string, null_type, less<string>, rb_tree_tag,
             tree_order_statistics_node_update> ost;

int op, g;
char name_in[40], s_in[40], e_in[40];
ost btree, gtree;

int num_less_than(string s, int g){
    if (g == 1){
        auto n = btree.lower_bound(s);

        if (n != btree.end()){
            return btree.order_of_key(*n);
        }
        else{
            return (int) btree.size();
        }
    }
    else{
        auto n = gtree.lower_bound(s);

        if (n != gtree.end()){
            return gtree.order_of_key(*n);
        }
        else{
            return (int) gtree.size();
        }
    }
          
}
int main(){
    while (1){
        scanf("%d", &op);
        if (op == 0)break;
        else if (op == 1){
            //add
            scanf("%s %d", name_in, &g);
            string name(name_in);
            if (g==1){
                btree.insert(name);
            }
            else if (g==2){
                gtree.insert(name);
            }
        }
        else if (op == 2){
            //remove
            scanf("%s", name_in);
            string name(name_in);
            btree.erase(name);
            gtree.erase(name);
        }
        else{
            //query
            scanf("%s %s %d", s_in, e_in, &g);
            string s(s_in);
            string e(e_in);
           
            int ans = 0;
            if (g==0 || g ==1){ // males
                ans += (num_less_than(e, 1) - num_less_than(s, 1));
            }
            if (g==0 || g==2){ // females
                ans += (num_less_than(e, 2) - num_less_than(s, 2));
            }

            printf("%d\n", ans);
        }
            
    }
}