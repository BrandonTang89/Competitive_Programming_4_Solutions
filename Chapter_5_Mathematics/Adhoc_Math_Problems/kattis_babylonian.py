'''
Kattis - babylonian
Simply convert from base 60 to base 10.
Time: O(n), Space: O(1)
'''
tc = int(input())
for _ in range(tc):
    arr = reversed([0 if x == "" else int(x) for x in input().split(',')])
    ans = 0
    b = 1
    for x in arr:
        ans += x * b
        b *= 60
    print(ans)
