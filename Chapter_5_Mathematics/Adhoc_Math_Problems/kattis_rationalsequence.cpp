/* Kattis - Rationalsequence
Despite the modest difficulty rating, quite a few observations are required to solve the problem rigourously 

Observation 0 (obvious):
    given a node p/q, p!=q, it is a right child if p>q and a left child if p<q
    ie it is a left child is the fraction is proper and a right child if the fraction is improper

Observation 1:
    from a node p/q to its successor in breath first search, we can traverse up to the first lowest left child
    ancestor and then one more level up to the least common ancestor of both p/q and the successor

    From there, we can traverse to the right child of the LCA and then the most extreme left child of that node
    in order to atain the successor node

    However, doing this naively results in O(height of tree) for each query which will TLE

Observation 2:
    Note that gcd(numerator, denominator) == 1 for all values on the tree. This means all
    input values will directly correspond to the numerator and denominator of values on the tree
    This is needed for observation 3 and 3.5 to be valid

    Proof:
        Assume there exist an integer a such that p = at, q = al, p!=q (else it would be the root)
        We find the above element
        if p < q:
            the above element is at/a(t+l)
        if p > q:
            the above elemennt is a(l-t)/l
        
        in both cases, both numerator and denominator can be divided by a again.
        This means the proceess can be repeated to eventually arrive at p=q=a, ie the root is not 1/1 but rather a/a
        thus p/q is not part of the original tree

Observation 3:
    When traversing from a right child node p/q to the parent,
    the parent has value p-q/q

    repeating this multiple times (assuming the parent is a right child itself all these times)
    the eventual ancestor has value (p-cq)/q for a parent c levels higher than the p/q
    
    Thus instead of traversing upward one step at a time, if we want to traverse c levels up at once, we just use (p-cq)/q

Observation 3.5:
    the most left child node c levels from a parent node p/q is p/(cp+q)
    This can be deduced similar to observation 3

Observation 4:
    to deterimine how many levels above the node p/q is the youngest left child ancestor (YLCA). Note that c = c=ceil(p/q - 1)
    
    Proof:
        0 < p - cd <= d as the YLCA has a proper fraction value
        p/q > c >= p/q-1 (after some manipulation)

Combining all observations, we can find the LCA and thus the successor in O(1) thus resulting in
Time: O(k), Mem: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

pair<int,int> traverse_down_right(int num, int denum){
    return make_pair(num+denum, denum);
}

pair<int,int> traverse_left_right(int num, int denum){
    int pnum = num;
    int pdenum = denum - num;
    return (traverse_down_right(pnum, pdenum));
}

int n, num, denum, dummy;
int main(){
    scanf("%d", &n);
    for (int t=0;t<n;t++){
        scanf("%d %d/%d", &dummy, &num, &denum);

        if (denum == 1){
            denum = num+1;
            num = 1;
        }
        else{
            int c=ceil((double)num/ (double)denum - 1);

            num -= denum*c;

            auto k = traverse_left_right(num, denum);
            num = k.first;
            denum = k.second;

            denum += num*c;
        }

        printf("%d %d/%d\n", dummy, num, denum);
    }
    return 0;
}