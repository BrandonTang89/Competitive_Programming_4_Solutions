'''
Kattis - harddrive
A kinda weird problem, we just need to believe that the strategy of going from right to left and putting 1s whenever we can get 2 bit changes
is optimal. We use the first bit to get an extra 1 if we have an odd number of bit changes.

Time: O(n), Space: O(n)
'''
n, c0, b = map(int, input().split())
c = c0
broken = set(map(int, input().split()))
broken = {x-1 for x in broken}

ans = [0] * n
cur = n-2

while cur > 0:
    if ans[cur+1] == 0 and c >= 2 and (cur not in broken):
        ans[cur] = 1
        c -= 2
    cur -= 1

if c == 1:
    assert ans[1] == 0
    ans[0] = 1
    c -= 1

assert c == 0
bitchanges = sum([(ans[i+1] ^ ans[i]) for i in range(n-1)])
assert bitchanges == c0
for br in broken:
    assert ans[br] == 0

print("".join(map(str, ans)))
