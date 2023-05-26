n = int(input())
strings = [input() for _ in range(n)]
child = [[] for _ in range(n)]
alive = [True for _ in range(n)]

for i in range(n-1):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    child[a].append(b)
    alive[b] = False

c = [i for i in range(n) if alive[i]][0]

def iteratative_dfs(x):
    stack = [x]
    while stack:
        y = stack.pop()
        print(strings[y], end='')
        for z in child[y][::-1]:
            stack.append(z)
iteratative_dfs(c)