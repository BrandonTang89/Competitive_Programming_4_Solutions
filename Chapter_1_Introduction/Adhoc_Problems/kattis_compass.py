'''
Kattis - compass
Simple math.

Time: O(1), Space: O(1)
'''
a, b = int(input()), int(input())
c = (b-a)%360

if c > 180:
    print(-(360-c))
else:
    print(c)