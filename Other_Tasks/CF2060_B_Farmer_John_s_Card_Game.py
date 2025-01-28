for _ in range(int(input())):
    n, m = map(int, input().split())
    can = True
    brr = []
    for j in range(n):
        arr = list(map(int, input().split()))
        arr.sort()
        diff = [arr[i+1] - arr[i] for i in range(len(arr)-1)]
        can = can and (all([d == n for d in diff]))
        brr.append((arr[0], j))
        
    if not can:
        print(-1)
        continue

    brr.sort()
    for _, i in brr:
        print(i+1, end=' ')
    print()