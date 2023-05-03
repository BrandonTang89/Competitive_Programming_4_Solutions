n = int(input())
print(-sum(filter(lambda x: x < 0, map(int, input().split()))))
