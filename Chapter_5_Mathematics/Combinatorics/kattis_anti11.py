'''
Kattis - anti11
Let f(x) be the number of x length binary strings without 11 ending with 1
Let g(x) be the numebr of x length binary strings without 11 ending with 0

f(2) = 1 {01}
g(2) = 2 {00, 10}

f(x+1) = g(x) {...01}
g(x+1) = f(x) + g(x) {...00, ...10}

ans(x) = f(x) + g(x)

Time: O(10000), Space: O(10000)
'''
M = int(1e9 + 7)

f = [0, 1, 1]
g = [0, 1, 2]

for i in range(2,10001):
    f.append(g[-1])
    g.append((g[-1] + f[-2]) % M)
    
# print(f[:10])
# print(g[:10])

n = int(input())
for i in range(n):
    x = int(input())
    print((f[x] + g[x])%M)