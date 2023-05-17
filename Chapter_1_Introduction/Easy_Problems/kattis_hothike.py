'''
Kattis - hothike
Adhoc, Easy.
Time: O(n), Space: O(n)
'''
n = int(input())
a = list(map(int, input().split()))
b = [(max(a[i], a[i+2]), i) for i in range(n-2)]
t, d = min(b)

print(d+1, t)