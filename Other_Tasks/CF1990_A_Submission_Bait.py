t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    
    count = {}
    for i in a:
        if i in count:
            count[i] += 1
        else:
            count[i] = 1
    
    # if count has an odd number then yes
    for i in count:
        if count[i] % 2 == 1:
            print("YES")
            break
    else:
        print("NO")
