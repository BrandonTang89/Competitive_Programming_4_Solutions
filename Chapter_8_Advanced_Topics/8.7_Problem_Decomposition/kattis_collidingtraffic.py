''' Kattis - collidingtraffic
Do some pen and paper solving to determine how to model the distance between any 2 boats. Then we just complete
search the time to collide between any 2 boats.

Time: O(n^2), Space: O(n)
'''
from math import radians, cos, sin, sqrt
num_tc = int(input())

def dist(x1, y1, x2, y2):
    return sqrt((x1 - x2)**2 + (y1 - y2)**2)


for _ in range(num_tc):
    n, r = input().split()
    n = int(n)
    r = float(r)
    boats = [list(map(float, input().split())) for _ in range(n)]

    for i in range(n):
        boats[i][2] = radians(boats[i][2])
    
    
    ans = 1e18
    for i in range(n):
        for j in range(i+1, n):
            x0, y0, theta0, s0 = boats[i]
            x1, y1, theta1, s1 = boats[j]
            
            if dist(x0, y0, x1, y1) <= r:
                ans = 0
                break
            
            dx = x0 - x1
            dy = y0 - y1
            
            dsx = s0 * sin(theta0) - s1 * sin(theta1)
            dsy = s0 * cos(theta0) - s1 * cos(theta1)

            a = dsx**2 + dsy**2
            b = 2 * (dx * dsx + dy * dsy)
            c = dx**2 + dy**2 - r**2
            
            discriminant = b**2 - 4 * a * c
            if (discriminant < 0 or a==0):
                continue
            
            time_to_collide = (-b - sqrt(discriminant)) / (2 * a)

            if (time_to_collide <= 0): continue
            ans = min(ans, round(time_to_collide))
            
        if ans == 0: break
    
    if ans == 1e18:
        print("No collision.")
    else:
        print(ans)
                
            