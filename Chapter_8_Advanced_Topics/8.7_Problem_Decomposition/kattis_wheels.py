'''
Kattis - wheels
Math + graph + geom. Quite easy, start by modeling the graph by doing a O(n^2) check to find
wheels that are touching each other and constructing an adjacency matrix. Then, do a dfs to 
colour the wheels as clockwise or anti-clockwise (or not moving). Then for each wheel, report
the movement and speed. We use the well known result that a moving wheel's speed only depends
on the ratio of the radii of the first wheel and the moving wheel (the intermediate wheel radii
get cancelled). Printing is efficient the use of the Fraction class to reduce the ratio by the GCD.

Time: O(n^2), Space: O(n^2)
'''
import fractions
tc = int(input())
for _ in range(tc):
    n = int(input())
    wheels = []  # (x, y, r)
    for _ in range(n):
        wheels.append(tuple(map(int, input().split())))

    adjmat = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(i+1, n):
            if (wheels[i][0] - wheels[j][0])**2 + (wheels[i][1] - wheels[j][1])**2 == (wheels[i][2] + wheels[j][2])**2:
                adjmat[i][j] = 1
                adjmat[j][i] = 1

    speed = [None for _ in range(n)]
    speed[0] = 1

    def dfs(u: int):
        for v in range(n):
            if adjmat[u][v] == 1 and speed[v] == None:
                speed[v] = -speed[u]
                dfs(v)

    dfs(0)
    for i in range(n):
        if speed[i] == None:
            print("not moving")
        else:
            print(fractions.Fraction(
                wheels[0][2], wheels[i][2]), "clockwise" if speed[i] > 0 else "counterclockwise")
