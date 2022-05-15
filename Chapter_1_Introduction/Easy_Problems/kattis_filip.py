'''
Kattis - filip
Reverse a number and compare. 

Time: O(1), Mem: O(1)
'''
(x, y) = input().split()
x = x[::-1]
y = y[::-1]

x = int(x)
y = int(y)

ans = max(x, y)
print(ans)
