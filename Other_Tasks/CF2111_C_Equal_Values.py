for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    ans = int(1e12)

    cur = -1
    cur_start = -1
    for i in range(n):
        if cur == arr[i]:
            continue
        
        # We consider the new row
        if cur_start != -1:
            ans = min(ans, cur_start * cur + (n-i) * (cur))
        
        cur = arr[i]
        cur_start = i
        
    ans = min(ans, cur_start * cur)
    print(ans)