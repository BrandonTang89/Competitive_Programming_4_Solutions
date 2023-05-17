'''
Kattis - thisaintyourgrandpascheckerboard
2D Array Manipulation, just do the checks on each row and column (nice to use transpose).
Time: O(n^2), Space: O(n^2)
'''
n = int(input())
a = [list(map((lambda x: 1 if x == 'W' else 0), input())) for _ in range(n)]
at = list(map(list, zip(*a)))

for i in range(n):
    if (sum(a[i]) != n//2):
        print(0)
        exit()
    if (sum(at[i]) != n//2):
        print(0)
        exit()

for i in range(n):
    for j in range(n-2):
        if (a[i][j] == a[i][j+1] and a[i][j] == a[i][j+2]):
            print(0)
            exit()
        if (at[i][j] == at[i][j+1] and at[i][j] == at[i][j+2]):
            print(0)
            exit()

print(1)