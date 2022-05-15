'''
Kattis - matrix
Calculate the inverse of a 2x2 matrix, pretty easy, just google for the formula

Time: O(1), Space: O(1)
'''
from sys import stdin
lines = stdin.readlines()
for line_num in range(0,len(lines),3):
    mat = []
    mat.append(list(map(int,lines[line_num].split())))
    mat.append(list(map(int,lines[line_num+1].split())))

    det = mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0] # ad - bc

    inverse = [[mat[1][1],-mat[0][1]],[-mat[1][0],mat[0][0]]] # [d, -b][-c, a]
    for i in range(2):
        for j in range(2):
            inverse[i][j] = inverse[i][j]//det

    print(f"Case {line_num//3 + 1}:") 
    for i in range(2):
        for j in range(2):
            print(inverse[i][j],end=' ')
        print()