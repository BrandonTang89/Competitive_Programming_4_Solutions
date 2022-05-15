'''
Kattis - candlebox
A basic arithmetic progression problem. Solve on paper first then code. Note the bruteforce of
the brother's age since solving it is too tiring

Time: O(brother age), Space: O(1)
'''
d = int(input())
R = int(input())
T = int(input())

t = 0
for i in range(10000):
    if (i+d)*(i+d+1)//2 + (i)*(i+1)//2 -9 == R+T:
        t = i
        break

r = t + d

print(R - (r*(r+1)//2 - 6))