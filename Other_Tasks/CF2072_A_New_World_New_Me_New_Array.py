for _ in range(int(input())):
    n, k, p = map(int, input().split())
    need = (abs(k) + p - 1) // p
    print(-1 if n < need else need)
    