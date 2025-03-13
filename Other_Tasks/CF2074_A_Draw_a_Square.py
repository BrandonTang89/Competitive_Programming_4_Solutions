for _ in range(int(input())):
    x = list(map(int, input().split()))
    print("Yes" if all([x[0] == y for y in x]) else "No")