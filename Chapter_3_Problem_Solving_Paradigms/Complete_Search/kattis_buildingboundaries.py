'''
Kattis - buildingboundaries
Sort of time waster problem that tests your code design skills. There are essentially 2 cases:
1. All 3 blocks are arranged in one line next to each other, assumed horizontally. We test all 2^3 orientations
of the blocks.
2. We have a top block ontop of a left block and a right block, the top block is flushed to the left and it is
is in contact with the left block. We test all 2^3 orientations of the blocks for the 3! ways to select the top
left and right blocks.

Time: O(1), Space: O(1)
'''
num_tc = int(input())
for _ in range(num_tc):
    x = list(map(int, input().split()))
    y = [(x[0],x[1]), (x[2],x[3]), (x[4],x[5])]

    ans = 1e20

    # Arrange in a Linear Straight Line
    for i in range(8):
        h = w = 0
        for j in range(3):
            if (i & (1 << j)):
                h = max(h, y[j][0])
                w += y[j][1]
            else:
                h = max(h, y[j][1])
                w += y[j][0]
        
        ans = min(ans, h*w)
    
    # print(ans)

    # Arrange 1 on top of 2, next to 3
    import itertools
    for per in itertools.permutations([0,1,2]):
        for i in range(8):
            tb = y[per[0]] # top block
            if (i & (1 << 0)): tb = (tb[1], tb[0]) # tb is now (height, width)
            
            lb = y[per[1]] # left block
            if (i & (1 << 1)): lb = (lb[1], lb[0])
            
            rb = y[per[2]] # right block
            if (i & (1 << 2)): rb = (rb[1], rb[0])
            
            if rb[0] > lb[0] and tb[1] > lb[1]: # position not possible, tb intersects rb
                continue
                
            h = max(tb[0] + lb[0], rb[0])
            w = max(tb[1], lb[1] + rb[1])
            
            ans = min(ans, h*w)
        
    print(ans)