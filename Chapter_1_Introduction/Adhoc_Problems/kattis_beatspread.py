'''
Kattis - beatspread
Very easy math problem.

Time: O(1), Space: O(1)
'''
num_tc = int(input())
for i in range(num_tc):
    a, b = map(int, input().split())
    
    l = (a+b)//2
    s = (a-b)//2
    
    if (a+b)%2 == 1 or s < 0:
        print(f"impossible")
    else:
        print(f"{l} {s}")