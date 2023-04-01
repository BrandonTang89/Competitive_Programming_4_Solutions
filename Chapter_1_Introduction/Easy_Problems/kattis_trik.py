# Kattis - trik
# Simple problem, simulation is probably the easiest way to solve it.
# Time: O(n)
a = 1
b = 0
c = 0
for s in input():
    if s == 'A':
        a, b = b, a
    elif s == 'B':
        b, c = c, b
    else:
        c, a, = a, c
    
if (a):
    print(1)
elif (b):
    print(2)
else:
    print(3)