'''
Kattis - npuzzle
Easy complete search question.

Time: O(1), Space: O(1)
'''
arr = [list(input()) for i in range(4)]

target = [
    ['A', 'B', 'C', 'D'], 
    ['E', 'F', 'G', 'H'],
    ['I', 'J', 'K', 'L'],
    ['M', 'N', 'O', '-'],
]

scatter = 0
for i in range(4):
    for j in range(4):
        for k in range(4):
            for l in range(4):
                if (arr[i][j] == target[k][l]):
                    scatter += abs(i - k) + abs(j - l)

print(scatter)