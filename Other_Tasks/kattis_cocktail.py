'''
Kattis - cocktail
Entry level greedy question, just try to drink the drinks in decreasing duration and 
check if each drink will last until the end of all drinks.

Time: O(n log n), Mem: O(n)
'''
n, t = map(int, input().split())
arr = sorted([int(input()) for _ in range(n)])[::-1]

possible = True
for i in range(n):
    if (arr[i] <= t*(n-i-1)):
        possible = False
        break

print ("YES" if possible else "NO")