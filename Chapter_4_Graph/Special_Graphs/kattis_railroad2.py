'''
Kattis - railroad2
This problem is just about judging whether an eulerian cycle exists. Each x junction has degree 4 
and each y junction has degree 3. Thus, since all nodes need to have even degree, the number of 
y junctions must be even.

Time: O(1), Space: O(1)
'''
x, y = map(int, input().split())

if (y%2 == 0):
    print("possible")
else:
    print("impossible")