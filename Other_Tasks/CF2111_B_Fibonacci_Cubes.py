
fibo = [-1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89]

for _ in range(int(input())):
    n, q = map(int, input().split())
    
    if n == 1:
        for _ in range(q):
            input()
            print(1, end="")
        print()
        continue
    
            
    biggest = fibo[n]
    second_biggest = fibo[n-1]
    
    for _ in range(q):
        arr = list(map(int, input().split()))
        arr.sort()
        
        if arr[0] >= biggest and arr[1] >= biggest and arr[2] >= biggest + second_biggest:
            print(1, end="")
        else:
            print(0, end="")
    print()
    