'''
Kattis - golombrulers
Use a hashmap and some loops.

Time: O(n^2), Space: O(n^2)
'''
from sys import stdin
for line in stdin:
    line = line.strip()
    arr = line.split()
    arr = [int(x) for x in arr]
    
    maxi = 1
    ruler = True
    s = set()
    for i in range(0, len(arr)):
        for j in range(i+1, len(arr)):
            x = abs(arr[j] - arr[i]) 
            if (x in s):
                ruler = False
                break
            s.add(x)
            maxi = max(maxi, x)
        if (not ruler):
            break
    
    if (not ruler):
        print("not a ruler")
        continue
    if (len(s) == maxi):
        print("perfect")
        continue
    
    print("missing", end=" ")
    for i in range(1, maxi+1):
        if (i not in s):
            print(i, end=" ")
    print()