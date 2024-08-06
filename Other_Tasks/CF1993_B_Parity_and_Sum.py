t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    
    evens = list(filter(lambda x: x % 2 == 0, arr))
    odds = list(filter(lambda x: x % 2 != 0, arr))
    
    if len(evens) == 0 or len(odds) == 0:
        print(0)
        continue

    cur = max(odds)
    evens.sort()
    bigeven = evens[-1]
    
    ans = 0
    for e in evens:
        while cur < e:
            cur += bigeven
            ans += 1

        cur += e
        ans += 1
    
    print(ans)
    
        