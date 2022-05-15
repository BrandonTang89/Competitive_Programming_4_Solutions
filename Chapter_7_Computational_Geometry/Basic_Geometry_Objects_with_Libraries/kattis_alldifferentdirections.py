'''
Kattis - alldifferentdirections
Essentially use robot style follow the walk commands and change the unit direction vector
based on the turning angle. Get the average of all destinations and get the distance between,
that and each of the individual directions. Print the average destination and the largest
distance between the average and an individual direction.

Time: O(n* num commands per person), Space: O(n)
'''
from math import cos, sin, pi
def rotate(direction, angle):
    return [direction[0] * cos(angle) - direction[1] * sin(angle),
            direction[0] * sin(angle) + direction[1] * cos(angle)]

def degtorad(deg):
    return deg * (2 * pi / 360)
while 1:
    n = int(input())
    if n == 0: break
    
    destinations = []
    for person in range(n):
        line = input().split()
        ln_pt = 0
        x, y = line.pop(0), line.pop(0)
        x, y = float(x), float(y)
        
        direction = [1, 0]
        line.pop(0)
        theta = float(line.pop(0))
        theta = degtorad(theta)
        
        direction = rotate(direction, theta)
        while len(line):
            op = line.pop(0)
            if op == "walk":
                dist = float(line.pop(0))
                x = x + direction[0] * dist
                y = y + direction[1] * dist
            elif op == "turn":
                theta = float(line.pop(0))
                theta = degtorad(theta)
                direction = rotate(direction, theta)
        
        destinations.append((x, y))
    
    average_dest = [0, 0]
    for d in destinations:
        average_dest[0] += d[0]
        average_dest[1] += d[1]
    average_dest[0] /= n
    average_dest[1] /= n
    
    print(average_dest[0], average_dest[1], end = ' ')
    
    distances = []
    for d in destinations:
        distances.append(((d[0] - average_dest[0])**2 + (d[1] - average_dest[1])**2)**0.5)
    print (max(distances))