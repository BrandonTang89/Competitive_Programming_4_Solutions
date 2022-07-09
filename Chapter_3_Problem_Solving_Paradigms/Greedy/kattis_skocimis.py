'''
Kattis - skocimis
Consider the larger of the 2 gaps between the 3 people, choose the larger gap and each iteration decrease this gap
by 1.

Time: O(1), Space: O(1)
'''
x, y, z = map(int, input().split())
ans = sorted([abs(x-y), abs(x-z), abs(y-z)])[1]
ans -= 1
print(ans)
