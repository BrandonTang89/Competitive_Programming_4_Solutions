for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    
    ans: list = []
    maxi = 0
    cur = sum(arr)
    for i in range(n):
        if maxi > arr[i]:
            ans.append(cur - arr[i] + maxi)
        else:
            ans.append(cur)
        
        maxi = max(maxi, arr[i])
        cur -= arr[i]

    print(*ans[::-1])