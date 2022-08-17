'''
Kattis - 99problems
Just do some basic modulo math to figure out the answer

Time: O(1), Space: O(1)
'''
n = int(input())

x = n % 100
if (x >= 49):
    print(n - x + 99)
elif (n - x == 0):
    print(99)
else:
    print((n//100 - 1)*100 + 99)
