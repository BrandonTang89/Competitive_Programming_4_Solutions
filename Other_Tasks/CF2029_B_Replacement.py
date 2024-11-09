t = int(input())

for _ in range(t):
    n = int(input())
    s = [int(x) for x in str(input())]
    
    ones = s.count(1)
    zeros = s.count(0)
    
    r = [int(x) for x in str(input())]
    
    if ones == 0 or zeros == 0:
        print("NO")
        continue
    
    for i in range(len(r)):
        if ones == 0 or zeros == 0:
            print("NO")
            break
        
        if r[i] == 0:
            ones -= 1
        else:
            zeros -= 1
        
    else:
        print("YES")