
for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    
    mini = min(arr)
    # mini needs mini + 1
    if n >= mini + 1:
        print(n)
    else:
        print(0)