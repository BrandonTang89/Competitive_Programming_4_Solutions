'''
Kattis - limbo2
Time waster. Just figure out the pattern and implement it. The idea is to find
out if the number is present in the section that is written in row major order
or column major order. Then we find the base position and the width/height of
the section and use a 2d array addressing style offset to find the answer.

Time: O(log n), Space: O(1)
'''
for _ in range(int(input())):
    y, x = map(int, input().split())

    msby = len(bin(y))-3
    msbx = len(bin(x))-3
    
    if y == 0: msby = -1
    if x == 0: msbx = -1
    if x == y == 0:
        print(0)
        continue

    if msby >= msbx: # row major order
        base = pow((1<<msby), 2) << 1
        w = (1<<msby) << 1
        print(base + (y-(1<<msby))*w + x)
    else:           # column major order
        base = pow((1<<msbx), 2)
        w = (1<<msbx)
        print(base + (x-(1<<msbx))*w + y)