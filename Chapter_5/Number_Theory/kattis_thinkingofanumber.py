'''
Kattis - thinkingofanumber
We observe that regarding the minimum and maximum, we only need to take the maximum lowerbound and the
minimum upperbound. As for the divisiblity, our final answer only needs to be divisble by the LCM
of all the numbers provided. We note that the final search space is small so we can brute force check
divisbility for all numbers between mini and maxi. If we needed to go faster, we could use the
use x0 + n*l to generate the required numbers.

Time: O(n), Space: O(1)
'''
from math import gcd
def lcm(a, b):
    return a * b // gcd(a, b)
while (1):
    n = int(input())
    if (n == 0):
        break
    l = 1
    
    maxi = -1
    mini = 1
    for _ in range(n):
        op1, op2, x = input().split()
        x = int(x)
        
        if (op1 == "less"):
            if (maxi == -1):
                maxi = x-1
                
            maxi = min(maxi, x-1)
        elif (op1 == "greater"):
            mini = max(mini, x+1)
        else:
            l = lcm(l, x)
            
    if (maxi == -1):
        print("infinite")
        continue
    if (maxi < mini):
        print("none")
        continue
        
    has_sol = 0
    for i in range(mini, maxi+1):
        if (i % l == 0):
            has_sol = 1
            print(i, end=" ")
    
    if (not has_sol):
        print("none", end="")
    print()
        
        

        
    
    