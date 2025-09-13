for _ in range(int(input())):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    arr = [(x // 100, x) for x in a]
    arr.sort()
    
    for i in range(n):
        # assign furthest classrooms
        bottom = arr[i//2][1]
        top = arr[m-(i//2)-1][1]

        if i%2 == 0:
            print(bottom, top, bottom, top, bottom, top)
        else:
            print(top, bottom, top, bottom, top, bottom)