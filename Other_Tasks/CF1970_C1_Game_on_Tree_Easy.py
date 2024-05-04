'''
CF1970 C1
Just refer to notes on question C2, this question subtask is not much easier than C2.
'''
import sys
n, t = map(int, input().split())

adjlist = [[] for _ in range(n)]

for _ in range(n-1):
    u, v = map(int, input().split())
    u-=1
    v-=1
    adjlist[u].append(v)
    adjlist[v].append(u)
    
# t = 1
start = int(input()) - 1

leftSide = adjlist[start][0]

if len(adjlist[start]) == 1: # edge case
    print("Ron" if (n-1)%t == 1 else "Hermione")
    exit()

rightSide = adjlist[start][1]

visited = [False]*n
visited[start] = True
visited[leftSide] = True
visited[rightSide] = True


def dfs(node):
    u = node
    ans = 1
    while (len(adjlist[u]) == 2):
        visited[u] = True
        for v in adjlist[u]:
            if not visited[v]:
                ans += 1
                u = v
                break

    return ans

left = dfs(leftSide)
right = dfs(rightSide)

if left % 2 == 1 or right % 2 == 1:
    print("Ron")
else:
    print("Hermione")
    