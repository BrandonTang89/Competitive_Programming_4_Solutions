for _ in range(int(input())):
    n, x = map(int, input().split())
    arr = [i for i in range(x)] + [i for i in range(x+1, n)] + ([x] if x < n else [])
    print(*arr)