'''
Kattis - temperature
x is the vertical intercept and y is the gradient of the B against A graph. Check for
B = A and B != A for all temperature values.

Else solve for B = yA + x = A

Time: O(1), Space: O(1)
'''
x, y = map(int, input().split())
if x == 0 and y == 1:
    print("ALL GOOD")
elif y == 1:
    print("IMPOSSIBLE")
else:
    print(x / (1-y))