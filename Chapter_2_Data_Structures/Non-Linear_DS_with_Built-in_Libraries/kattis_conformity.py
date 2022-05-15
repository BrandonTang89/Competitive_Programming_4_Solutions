'''
Kattis - conformity
Another relatively easy question. Note that python has built in support for hashing tuples in a
hashtable while C++ does not. Remember to sort before hashing.

Time: O(n), Space: O(n)
'''
n = int(input())
hashmap = {}

for i in range(n):
    s = tuple(sorted(input().split()))
    
    if not s in hashmap:
        hashmap[s]= 0
    hashmap[s] += 1
    
m = max(hashmap.values())
ans = 0
for val in hashmap.values():
    if val == m:
        ans += val
print(ans)