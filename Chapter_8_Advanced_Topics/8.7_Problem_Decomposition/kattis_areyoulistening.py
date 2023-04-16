# Kattis - areyoulistening
# Geometry + Binary Search. We can do a check for a certain radius in O(n), so we can do a binary search
# for the maximum radius that works.
# Time: O(n * 100), Mem: O(n)
def circlesoverlap(cx1, cy1, r1, cx2, cy2, r2):
    return (cx1 - cx2) ** 2 + (cy1 - cy2) ** 2 < (r1 + r2) ** 2

x, y, n = map(int, input().split())
x = float(x)
y = float(y)

listeners = [(x, y, r) for x, y, r in [map(int, input().split()) for _ in range(n)]]

def any3circleoverlap(r):
    num_overlaps = 0
    for x2, y2, r2 in listeners:
        if circlesoverlap(x, y, r, x2, y2, r2):
            num_overlaps += 1
            if num_overlaps == 3:
                return True
    return False

l = 0.0
r = 3000.0
for i in range(100):
    m = (l + r) / 2
    if any3circleoverlap(m):
        r = m
    else:
        l = m

print(int(l))