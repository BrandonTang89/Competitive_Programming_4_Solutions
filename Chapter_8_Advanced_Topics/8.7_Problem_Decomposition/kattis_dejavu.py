# Kattis - dejavu
# Easy question. For each point, number of right triangles with that point as the right angled vertex
# is (number of points with same x coordinate - 1) * (number of points with same y coordinate - 1).
n = int(input())
pts = [(int(x), int(y)) for x, y in [input().split() for _ in range(n)]]
xs = [0] * int(1e5+1)
ys = [0] * int(1e5+1)

for x, y in pts:
    xs[x] += 1
    ys[y] += 1

ans = 0
for x, y in pts:
    ans += (xs[x]-1) * (ys[y]-1)

print(ans)