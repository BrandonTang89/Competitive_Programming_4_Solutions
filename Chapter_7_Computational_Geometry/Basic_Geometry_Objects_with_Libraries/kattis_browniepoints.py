'''
Kattis - browniepoints
Annoying problem description which needs to be read closely. The line drawn passes through
the point in the center of the input sequence.

Time: O(n), Space: O(n) 
'''
class point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __str__(self):
        return "(" + str(self.x) + ", " + str(self.y) + ")"
    def __repr__(self):
        return "(" + str(self.x) + ", " + str(self.y) + ")"
    def __add__(self, other):
        return point(self.x + other.x, self.y + other.y)
    def __sub__(self, other):
        return point(self.x - other.x, self.y - other.y)
    def __mul__(self, other):
        return point(self.x * other, self.y * other)
    def __truediv__(self, other):
        return point(self.x / other, self.y / other)
    def __floordiv__(self, other):
        return point(self.x // other, self.y // other)
    def __eq__(self, other):
        return self.x == other.x and self.y == other.y
    def __ne__(self, other):
        return self.x != other.x or self.y != other.y
    def __neg__(self):
        return point(-self.x, -self.y)
    def __abs__(self):
        return point(abs(self.x), abs(self.y))
    def __bool__(self):
        return self.x != 0 or self.y != 0
    def __ge__(self, other):
        return self.x >= other.x and self.y >= other.y
    def __gt__(self, other):
        return self.x > other.x and self.y > other.y
    def _le__(self, other):
        return self.x <= other.x and self.y <= other.y
    def _lt__(self, other):
        return self.x < other.x and self.y < other.y
    
    # Returns a point rotated about the origin by theta radians
    def rotate(self, theta):
        return point(self.x * cos(theta) - self.y * sin(theta), self.x * sin(theta) + self.y * cos(theta))

while True:
    stan = ollie = 0
    n = int(input())
    if (n == 0):
        break
    points = []
    for i in range(n):
        p = point(*map(int, input().split()))
        points.append(p)
        
        if (i == n//2):
            center = p
    
    for p in points:
        p -= center
        if p.x > 0 and p.y > 0:
            stan += 1
        elif p.x < 0 and p.y < 0:
            stan += 1
        elif p.x > 0 and p.y < 0:
            ollie += 1
        elif p.x < 0 and p.y > 0:
            ollie += 1
    print(stan, ollie)