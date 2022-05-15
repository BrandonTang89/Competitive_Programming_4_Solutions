'''
Kattis - trollhunt
Basic math, note that we don't need to search the intial bridge the troll was on.

Time: O(1), Space: O(1)
'''
from math import ceil
t, k, g = map(int, input().split())
ans = ceil((t-1)/(k//g))
print(ans)