
t = int(input())

for _ in range(t):
    n = int(input())
    sticks = list(map(int, input().split()))
    
    counter = {}
    for stick in sticks:
        if stick in counter:
            counter[stick] += 1
        else:
            counter[stick] = 1
    
    ans = 0    
    for (key, value) in counter.items():
        ans += (value // 3)
    
    print(ans)