for _ in range(int(input())):
    a, b, d, e = map(int, input().split())
    arr = [a+b, d-b, e-d]
    
    print(arr.count(max(set(arr), key=arr.count)))