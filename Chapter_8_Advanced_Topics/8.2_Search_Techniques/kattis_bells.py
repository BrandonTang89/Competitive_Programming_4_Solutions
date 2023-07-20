'''
Kattis - bells
Constructive problem. While this is in the recursive backtracking section, the best solution
is this constructive one I believe. The idea is the largest element moves from right to left
while the other numbers "don't move" relative to each other. Then we "update" the positions
of the elements except the largest element (which has been precomputed), and sweep the 
largest element from left to right again. We do this repeatedly an even number of times
(since n! is even for all n >= 2), so we will end up in a position that can return to the start.

The largest element kinda follows the blue line in the question (for visualisation).

Kind of a neat solution. 

Time: O(n * n!), Space: O(n * n!)
'''
n = int(input())

performance = [[] for _ in range(n)]
performance[0] = [[0]]

for cur in range(1, n):
    cur_pos = cur
    direction = -1
    for line in performance[cur-1]:
        if direction == -1:
            for pos in range(cur, -1, -1):
                performance[cur].append(line[:pos] + [cur] + line[pos:])
        else:
            for pos in range(cur+1):
                performance[cur].append(line[:pos] + [cur] + line[pos:])
                
        direction *= -1
    
for line in performance[-1]:
    print(' '.join(str(i+1) for i in line))