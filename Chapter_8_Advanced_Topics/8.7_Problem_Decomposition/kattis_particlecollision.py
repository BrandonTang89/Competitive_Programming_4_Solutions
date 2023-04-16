# Kattis - particlecollision
# Math + Geometry. To determine if a particle will collide with another, we model the path of the moving
# particle as a line and see when it will intersect a circle of radius 2r with the center being that of
# the stationary particle. This forms a quadratic equation with parameter t that we solve for. To determine
# the new trajectory of a particle after a collision, we find the vector connecting the 2 centers
# of the particles during collision and normalize it. 
# Not too hard but could be tedious.
# Time: O(1), Mem: O(1)
import math
def quadhassolutions(a, b, c):
    return b*b - 4*a*c >= 0

def getquadsolutions(a, b, c):
    if not quadhassolutions(a, b, c):
        return None
    d = math.sqrt(b*b - 4*a*c)
    return (-b - d) / (2*a), (-b + d) / (2*a)

def gettimeofcollision(xm, ym, vx, vy, xs, ys, r): # (xm, ym) is moving at (vx, vy), (xs, ys) is stationary
    c = xm - xs
    d = ym - ys
    
    ret = getquadsolutions(vx*vx + vy*vy, 2*(vx*c + vy*d), c*c + d*d - 4*r*r)
    
    if (ret == None):
        return None
    
    t1, t2 = ret
    assert(t1 <= t2)
    if t1 < 0 and t2 < 0:
        return None
    if t1 < 0:
        return t2
    return t1
    

def getnewdirection(xm, ym, vx, vy, xs, ys, r):
    c = xm - xs
    d = ym - ys
    
    t = gettimeofcollision(xm, ym, vx, vy, xs, ys, r)
    if t == None:
        return None
    
    x = xm + vx*t
    y = ym + vy*t
    
    dx = xs - x
    dy = ys - y
    
    l = math.sqrt(dx*dx + dy*dy)
    dx /= l
    dy /= l
    
    return dx, dy


x1, y1 = map(float, input().split())
x2, y2 = map(float, input().split())
x3, y3 = map(float, input().split())
vx1, vy1, r = map(float, input().split())

timetopart2 = gettimeofcollision(x1, y1, vx1, vy1, x2, y2, r)
timetopart3 = gettimeofcollision(x1, y1, vx1, vy1, x3, y3, r)

if timetopart2 == None and timetopart3 == None: 
    print(5)
    exit()

if timetopart2 != None and (timetopart3 == None or timetopart2 < timetopart3):
    vx2, vy2 = getnewdirection(x1, y1, vx1, vy1, x2, y2, r)
    
    ntimetopart3 = gettimeofcollision(x2, y2, vx2, vy2, x3, y3, r)
    if ntimetopart3 == None:
        print(3)
        exit()

    print(1)
    exit()

if (timetopart3 != None) and (timetopart2 == None or timetopart3 < timetopart2):
    vx3, vy3 = getnewdirection(x1, y1, vx1, vy1, x3, y3, r)
    
    ntimetopart2 = gettimeofcollision(x3, y3, vx3, vy3, x2, y2, r)
    if ntimetopart2 == None:
        print(4)
        exit()
    
    print(2)
    exit()