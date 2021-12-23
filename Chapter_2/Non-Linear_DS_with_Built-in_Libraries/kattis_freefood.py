'''
Kattis - freefood
Super easy problem. Could be harder and require a fenwick tree or sth, but meh.

Time: O(n), Space: O(1)
'''
n = int(input())
arr = [False] * 365

for i in range(n):
    s, e = map(int, input().split())
    s -= 1
    e -= 1

    for j in range(s, e+1):
        arr[j] = True

ans = sum(arr)
print(ans)