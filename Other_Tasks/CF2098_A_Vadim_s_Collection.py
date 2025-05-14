for _ in range(int(input())):
    x = [int(i) for i in list(input())]
    x.sort()
    
    ans = ""
    avail = []
    for i in range(10):
        to_add = 9 - i
        while x and x[-1] == to_add:
            avail.append(to_add)
            x.pop()
        ans += str(avail[-1])
        avail.pop()
    
    print(ans)