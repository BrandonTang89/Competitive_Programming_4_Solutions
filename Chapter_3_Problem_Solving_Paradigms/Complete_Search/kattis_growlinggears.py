'''
Kattis - growlinggears
Compare the max height of the parabolas, get the index of the parabola with the largest height

Time: O(n), Space: O(1)
'''
num_tc = int(input())
for _ in range(num_tc):
    n = int(input())
    cur_max = -10000
    cur_index = -1
    for i in range(n):
        a, b, c = map(int, input().split())
        r = b/(a*2)
        
        if cur_max < -a*r*r + b*r + c:
            cur_max = -a*r*r + b*r + c
            cur_index = i

    print(cur_index+1)    