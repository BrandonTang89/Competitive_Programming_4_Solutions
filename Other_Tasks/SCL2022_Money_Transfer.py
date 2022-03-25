'''
Shopee Code League 2022 - Money Transfer
Entry level problem.
'''
n, t = map(int, input().split())

d = {}
for i in range(n):
    a, b = input().split()
    b = int(b)
    
    d[a] = b

for i in range(t):
    u, v, amt = input().split()
    amt = int(amt)
    if d[u] < amt:
        continue
    d[u] -= amt
    d[v] += amt

d = sorted(d.items(), key=lambda x: x[0])
for k,v in d:
    print(k, v)