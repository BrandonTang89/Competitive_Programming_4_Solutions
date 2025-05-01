for _ in range(int(input())):
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    brr = list(map(int, input().split()))
    x = [(a + b) for a, b in zip(arr, brr) if b >= 0]
    
    if len(x) == 0:
        smallest_x = max(arr)
        biggest_x = k + min(arr)
        print(max(0, biggest_x - smallest_x + 1))
        continue

    if all(q == x[0] for q in x):
        q = x[0]
        can = all(q - a >= 0 and q - a <= k for (a, b) in zip(arr, brr) if b < 0)
        print(1 if can else 0)
    else:
        print(0)
