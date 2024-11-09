t = int(input())
for _ in range(t):
    l, r, k = map(int, input().split())
    q = r//k
    print(max(0, q-l+1))