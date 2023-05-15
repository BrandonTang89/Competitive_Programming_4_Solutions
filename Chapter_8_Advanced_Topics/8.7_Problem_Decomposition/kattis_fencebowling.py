'''
Kattis - fencebowling
Just BSTA for length of where the ball will be at the middle of the lane after k bounces as you vary beta.

Time: O(k * 100), Space: O(1)
'''
from math import tan, atan
k, w, l = map(int, input().split())
def lengthWithBeta(beta: float):
    total_length = (w/2) * tan(beta)
    
    for i in range(k):
        beta = atan(2*tan(beta))
        
        if i < k-1:
            total_length += (w) * tan(beta)
        else:
            total_length += (w/2) * tan(beta)
    
    return total_length

le = 0
ri = 1.57079632679 # pi/2

for _ in range(100):
    mid = (le+ri)/2
    if lengthWithBeta(mid) > l:
        ri = mid
    else:
        le = mid
        
print(le * 180 / 3.14159265359)