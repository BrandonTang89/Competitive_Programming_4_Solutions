'''
Kattis - cetiri
Sort and then 3 cases.

Time: O(1), Space: O(1)
'''
a, b, c = sorted(map(int, input().split()))

if c - b == b - a:
    print(c + (c - b))
elif abs(c - b) > abs(b - a):
    print(b + (b - a))
elif abs(c- b) < abs(b - a):
    print(a + (c - b))