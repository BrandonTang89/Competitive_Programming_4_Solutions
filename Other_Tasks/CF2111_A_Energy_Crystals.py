
for _ in range(int(input())):
    x = int(input())
    
    arr = [0, 0, 0]
    ans = 0
    while min(arr) < x:
        arr.sort()
        arr[0] = arr[1]*2+1
        ans += 1
    print(ans)
