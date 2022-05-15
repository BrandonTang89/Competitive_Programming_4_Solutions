'''
Kattis - videospeedup
Do some basic math, use a for loop.

Time: O(n), Space: O(n)
'''

n, p, k = map(int, input().split())
p/=100
t = list(map(int, input().split()))

t.insert(0, 0)
t.append(k)

ans = 0
for i in range(0, n+1):
    ans += (t[i+1] - t[i]) * (1 + i*p)

print(ans)