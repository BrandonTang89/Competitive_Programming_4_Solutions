for _ in range(int(input())):
    n = int(input())
    x = list(map(int, input().split()))
    print(sum(x) - len(x) + 1)