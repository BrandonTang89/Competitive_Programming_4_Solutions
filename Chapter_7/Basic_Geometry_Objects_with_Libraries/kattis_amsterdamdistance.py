'''
Kattis - amsterdamdistance
The key observation is that given any path, we can always find a better than or equal path by
first going from the start to the inner most ring traversed along the path and then 
moving to the same angle as the end then going to the end. This is because for any change in angle
a more inner ring would result in a shorter path.

Thus, we can be sure that there exist an optimal path of the form: move from start to a ring
that is at least as in as the most in as the inner of the start and end. Then move along that
ring until in line with the end then go to the end. So we just need to try all rings
inner than the more inner of the start and end.
'''
m, n, r = input().split()
n, m = int(n), int(m)
r = float(r)

from math import pi as PI
def along_arc(s, e, arc_num):
    radius = r / n * arc_num
    return abs(s - e) * (PI * radius) / m

def along_line(s, e):
    return r/n * abs(s - e)

x1, y1, x2, y2 = map(int, input().split())
if (y1, x1) > (y2, x2):
    x1, y1, x2, y2 = x2, y2, x1, y1

# print(x1, y1, x2, y2)

ans = 1000000
for y in range(0, y1+1):
    ans = min(ans, along_line(y, y1) + along_arc(x1, x2, y) + along_line(y, y2))
    # print(y, ans)
    
print(ans)