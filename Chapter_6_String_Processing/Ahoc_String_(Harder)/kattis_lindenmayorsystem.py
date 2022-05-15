'''
Kattis - lindenmayorsystem
We opt not to use regex since it seems more tedious. Just loop over the string with a map.
Note the dumb edge cases that t can be 0.

Time: O(nm), Space: O(n)
'''
x, t = map(int, input().split())
d = dict()
for i in range(x):
    a, c, b = input().split()
    d[a] = b

p = input()
ans = p
for _ in range(t):
    ans = ""
    for i in p:
        if i in d:
            ans += d[i]
        else:
            ans += i
    p = ans
print(ans)
