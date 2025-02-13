t = int(input())
for _ in range(t):
    x, y = map(int, input().split())
    if x + 1 == y:
        print("Yes")
        continue
    if x < y:
        print("No")
        continue
    
    if (x - y) % 9 == 8:
        print("Yes")
    else:
        print("No")