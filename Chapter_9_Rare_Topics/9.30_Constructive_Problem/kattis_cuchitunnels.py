'''
Kattis - cuchitunnels
Super easy problem. We go from left to right, and just shove each new room anywhere and keep track of the number of branches
without rooms on their ends. The key observation is that where exactly we put each room doesn't matter if we process the rooms
from left to right.

Time: O(n), Space: O(1)
'''
n = int(input())
arr = list(map(int, input().split()))
numAvail = arr[0]
for i in range(1, n):
    if numAvail == 0:
        print("NO")
        exit()
    numAvail = numAvail - 2 + arr[i]
if numAvail == 0:
    print("YES")
else:
    print("NO")
