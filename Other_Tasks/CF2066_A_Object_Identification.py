import sys
for _ in range(int(input())):

    n = int(input())   
    xs = [int(x) for x in input().split()]
    
    # MEX
    mex = 1
    s = set(xs)
    while mex in s:
        mex += 1
    
    if mex < n+1:
        print(f"? {mex} {1 if mex > 1 else 2}")
        sys.stdout.flush()
        res = int(input())
        if res == 0:
            print(f"! A")
            sys.stdout.flush()
        else:
            print(f"! B")
            sys.stdout.flush()
    else:
        for i in range(n):
            if xs[i] == 1:
                a = i+1
            if xs[i] == n:
                b = i+1
                
        assert a is not None and b is not None
        
        print(f"? {a} {b}")
        sys.stdout.flush()
        
        res = int(input())
        if res < n-1: 
            print(f"! A")
            sys.stdout.flush()
        else:
            print(f"? {b} {a}")
            sys.stdout.flush()
            res = int(input())
            if res < n-1:
                print(f"! A")
                sys.stdout.flush()
            else:
                print(f"! B")
                sys.stdout.flush()