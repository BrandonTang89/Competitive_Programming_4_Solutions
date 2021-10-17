'''
Kattis - torn2pieces

I contemplated abit between using python or C++ for this. While i'm more well versed at implementing graph algorithms in C++, python allows easier use
of strings as the nodes rather than having to annoyingly convert between the strings and integer vertices. That being said, do remember to check
whether the piece of information about a specific vertices neighbours are present before attempting to traverse to their neighbours to prevent RTE.

Time: O(V + E), Mem: O(V^2), such high memory since we store the path at every DFS call.. but okay with small graphs here
If it was a bigger graph, we would have computed dist with BFS and done a backtrack from end to source. Also we would have used C++
since time would have been more important.
'''
n = int(input())

visited = {}
adjlist = {}
for _ in range(n):
    line = input().split(" ")
    u = line[0]
    visited[u] = 0
    if not (u in adjlist):
        adjlist[u] = []

    for v in line:
        if v == u: #don't put the self-loop in 
            continue

        adjlist[u].append(v)

        visited[v] = 0
        if v in adjlist:
            adjlist[v].append(u)
        else:
            adjlist[v] = [u]

line = input().split()
start = line[0]
target = line[1]

target_path = []
def dfs(u, path):
    path_new = path.copy()
    path_new.append(u)
    visited[u] = 1

    if (u == target):
        global target_path
        target_path = path_new
        return

    if u in adjlist: #important check
        for k in adjlist[u]:
            if not k in visited:
                visited[k] = 0
                
            if visited[k] == 0:
                dfs(k, path_new)

dfs(start, [])

if len(target_path) > 0: 
    ans = ""
    for s in target_path:
        ans += s + " "
    print(ans[:-1])
else:
    print("no route found")
