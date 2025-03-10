for _ in range(int(input())):
    n, x = map(int, input().split())
    print("YES" if sum(map(int, input().split())) == n * x else "NO")
