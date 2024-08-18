t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))

    if n > 2 or arr[0] + 1 == arr[1]:
        print("NO")

    else:
        print("YES")
