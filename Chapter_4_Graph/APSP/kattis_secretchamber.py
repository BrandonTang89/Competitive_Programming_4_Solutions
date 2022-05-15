''' Kattis - secretchamber
Without much execution time pressure along with nodes being characters, we opt to use python with a
dict of dicts as our adjacency matrix. This is basically just floyd warshall transitive closure.

Time: O(V^3), Mem: O(V^2)
'''
n, q = input().split()
n = int(n)
q = int(q)

edges = []
node_names = set()
for i in range(n):
    u, v = input().split()
    edges.append((u,v))
    node_names.add(u)
    node_names.add(v)

adjmat = {}
for i in node_names:
    adjmat[i] = {}
    for j in node_names:
        adjmat[i][j] = 0

for u, v in edges:
    adjmat[u][v] = 1

for k in node_names:
    for i in node_names:
        for j in node_names:
            adjmat[i][j] |= adjmat[i][k] & adjmat[k][j]

for _ in range(q):
    a, b = input().split()
    if len(a) != len(b):
        print("no")
        continue

    no = 0
    for i in range(len(a)):
        if (a[i] == b[i]):
            continue
        
        if not(a[i] in node_names and b[i] in node_names):
            no = 1
            break
            
        if (adjmat[a[i]][b[i]] == 0):
            no = 1
            break

    if no:
        print("no")
    else:
        print("yes")
