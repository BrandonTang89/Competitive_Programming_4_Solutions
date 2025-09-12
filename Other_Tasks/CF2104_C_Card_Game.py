for _ in range(int(input())):
    n = int(input())
    a: set[int] = set()
    b: set[int] = set()
    
    x = list(input().strip())
    
    for i in range(n):
        if x[i] == 'A':
            a.add(i+1)
        else:
            b.add(i+1)
    
    if 1 in a and n in a:
        print("Alice")
    elif 1 in b and n in b:
        print("Bob")
    elif 1 in b and n in a and n-1 in b:
        print("Bob")
    elif 1 in b and n in a and n-1 in a:
        print("Alice")
    elif 1 in a and n in b and n-1 in b:
        print("Bob")
    
    else:
        assert 1 in a and n in b and n-1 in a
        
        if len(b) == 1:
            print("Alice")
        else:
            print("Bob")