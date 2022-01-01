'''
Kattis - skener
Easy problem.

Time: O(h*zh + w*zw), Space: O(w*zw)
'''
h, w, zh, zw = map(int, input().split())
grid = []
for _ in range(h):
    ori_line = list(input())
    line = [x*zw for x in ori_line]
    for i in range(zh):
        print(''.join(line))