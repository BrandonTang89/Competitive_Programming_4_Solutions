'''
Kattis - splat
Simple geom problem. Just see which is the latest drop that is within the radius of the point.
Time: O(nq), Space: O(n)
'''
PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286
def dist(a, b):
    (x1, y1) = a
    (x2, y2) = b
    return ((x1-x2)**2 + (y1-y2)**2)**0.5

tc = int(input())
for _ in range(tc):
    n = int(input())
    drops = [input().split() for _ in range(n)][::-1]
    drops = [(float(x), float(y), ((float(v)/PI)**0.5), col) for x, y, v, col in drops]
    drops.append((0, 0, 10000, "white"))
    
    q = int(input())
    for _ in range(q):
        px, py = map(float, input().split())
        for (x, y, r, c) in drops:
            if dist((px, py), (x, y)) <= r:
                print(c)
                break