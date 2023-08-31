'''
Kattis - eulersnumber
Simple loop.
Time: O(n), Space: O(1)
'''
n = int(input())
e = 0
ifact = 1
for i in range(n+1):
    e += 1 / ifact
    ifact *= (i + 1)
print(e)