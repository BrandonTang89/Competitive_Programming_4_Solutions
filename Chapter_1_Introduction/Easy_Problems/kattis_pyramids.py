'''
Kattis - digitswap
Just brute force.

Time: O(sqrt(n)), Space: O(1)'''
n = int(input())

for i in range(1, 100000000, 2):
    n -= i**2
    if (n < 0):
        print(i//2)
        break