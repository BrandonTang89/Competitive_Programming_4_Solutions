'''
Kattis - hangingout
Simple simulation.

Time: O(n), Space: O(1)
'''
c, n = map(int, input().split())
cur = 0
ans = 0
for _ in range(n):
    op, x = input().split()
    x = int(x)
    
    if op == "leave":
        cur -= x
    else:
        if cur + x > c:
            ans += 1
        else:
            cur += x
print(ans)