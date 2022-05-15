'''
Kattis - tarifa
Basic.

Time: O(n), Space: O(1)
'''
x = int(input())
n = int(input())
ans = 0
for _ in range(n):
    ans += x - int(input())
print(ans + x)