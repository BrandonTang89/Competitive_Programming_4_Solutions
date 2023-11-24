'''
Kattis - password
E(X) = 1 * p1 + 2 * p2 + 3 * p3 + ... + n * pn
where the p values are ordered in decreasing order.

Time: O(n log n), Space: O(n)
'''
n = int(input())
d = sorted([float(list(input().split())[1]) for _ in range(n)], reverse=True )
ans = sum(map(lambda x: x[0]*x[1], zip(range(1, n+1), d)))
print(ans)