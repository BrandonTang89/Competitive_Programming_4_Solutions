'''
Kattis - grandpabernie
Use a hashmap of sorted vectors!

Time: O(n + q), Space: O(n)
'''
n = int(input())
hashmap = {}
for i in range(n):
    c, year = input().split()
    year = int(year)
    if not c in hashmap:
        hashmap[c] = []
    
    hashmap[c].append(year)

for c in hashmap:
    hashmap[c].sort()

q = int(input())
for _ in range(q):
    c, i = input().split()
    i = int(i) - 1
    
    print(hashmap[c][i])