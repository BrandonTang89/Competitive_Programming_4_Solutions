'''
Kattis - otherside
Another kinda time waster problem. 

We consider the subproblem: 
    Entity A cannot exist with entity B. What is the minimum weight of boat required to move
    all of A and B to the other side?
    
There is only 1 good strategy: 
    Suppose |B| <= 2*|A|, then we can achieve this with a |A| boat by moving all of A over, 
    then coming back and grabbing |A| of B. On the right, we swap to put all the As on the boat, 
    then go to the left and swap over again to get all the remaining Bs. Then we put them
    on the right and go back for the As.
    
    If |B| > 2*|a| we can use a |A|+1 boat by just holding all |A| of A and moving 1 B over at a time.
    
    It is clearly not possible to use anything < |A| since after the first step we will have at least 
    1 A and 1 B on the left.

Despite "eats" being an anti-symmetric relation, "cannot exist with" is actually symmetric. So in general we can just assume
A to be sheep and B to be wolfs or cabbages then we apply the above strategy.

Time: O(1), Space: O(1)
'''
w, s, c, k = map(int, input().split())

c += w
s, c = max(s, c), min(s, c)  # s >= c

if s <= 2 * c:
    req = c
else:
    req = c + 1

if req <= k:
    print("YES")
else:
    print("NO")