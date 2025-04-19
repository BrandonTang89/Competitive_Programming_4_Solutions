from collections import defaultdict
for _ in range(int(input())):
    
    n = int(input())
    pts: list[tuple[int, int]] = []
    for i in range(n):
        x, y = map(int, input().split())
        pts.append((x, y))
        
    by_x: dict[int, list[int]] = defaultdict(lambda: []) # number of y at point x
    for i in range(n):
        by_x[pts[i][0]].append(pts[i][1])
    
    # get the only one with an odd number of y
    odd_x = None
    for x, ys in by_x.items():
        if len(ys) % 2 == 1:
            odd_x = x
            break
    
    assert odd_x is not None, "There should be an odd number of y at some x"
    
    # print("the x", odd_x)
    
    s = set(y for y in by_x[odd_x]) # items on the odd_x
    
    for x in by_x:
        if x == odd_x:
            continue
        
        if x < odd_x:  # shift downward
            diff = odd_x - x
            for y in by_x[x]:
                ny = y - diff
                if ny in s:
                    s.remove(ny)
                else:
                    s.add(ny)
        else:  # shift upward
            diff = x - odd_x
            for y in by_x[x]:
                ny = y + diff
                if ny in s:
                    s.remove(ny)
                else:
                    s.add(ny)
    
    assert len(s) == 1, "There should be only one y left"
    
    print(odd_x, s.pop())
    
    