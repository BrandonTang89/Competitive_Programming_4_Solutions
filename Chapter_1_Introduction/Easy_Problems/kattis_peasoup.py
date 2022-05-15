'''
Kattis - peasoup
Just check membership in set.

Time: O(sum(m) + n), Space: O(m)
'''
n = int(input())
for _ in range(n):
    m = int(input())
    name = input()
    s = set(input() for i in range(m))
    if "pea soup" in s and "pancakes" in s:
        print(name)
        exit()
print("Anywhere is fine I guess")
    