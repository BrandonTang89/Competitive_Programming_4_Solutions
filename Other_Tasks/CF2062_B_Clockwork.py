for _ in range(int(input())):
    
    n = int(input())
    
    arr = [int(x) for x in input().split()]
    
    for i in range(n):
        if arr[i] <= 2*i:
            print("NO")
            break
        if arr[i] <= 2*(n-i-1):
            print("NO")
            break
    else:
        print("YES")
    