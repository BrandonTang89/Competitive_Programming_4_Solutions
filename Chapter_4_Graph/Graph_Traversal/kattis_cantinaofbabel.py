''' 
Kattis - cantiaofbabel
The tricky part of this question is not really the SCC part as it is quite standard but rather constructing the directed graph.
Good thing tho, n <= 100 so our O(n^2 * 20) relatively naive method will work. If we need to be more efficient,
we can construct a set of language listeners for each language. Then for each person, we do a O(20 * log n) check, 
allowing for O(n log n * 20) overall complexity. However, this is overkill in our case.

After building the graph, run the standard Tarjan SCC algorithm and alls good to go.

Time: O(V^2), Mem: O(V + E)
'''
n = int(input())

people = []
for i in range(n):
    line = input().split()
    people.append(line[1:])


# Build Graph in O(n^2 * 20)
adjlist = []
for u in range(n):
    s = set()
    spoken_lang = people[u][0]
    for v in range(n):
        if u == v:
            continue
        for lang in people[v]:
            if lang == spoken_lang:
                s.add(v)
                break
    
    adjlist.append(s)


# SCC Finding Tarjan
dfsNumberCounter = 0
dfs_num = [-1]*n
dfs_low = [0]*n
visited = [False]*n
st = []
max_scc_size = 0

def tarjanSCC(u):
    global dfsNumberCounter
    global max_scc_size
    global st
    dfs_low[u] = dfsNumberCounter
    dfs_num[u] = dfsNumberCounter
    dfsNumberCounter+=1
    st.append(u)
    visited[u] = True

    for v in adjlist[u]:
        if dfs_num[v] == -1:
            tarjanSCC(v)
        if visited[v]:
            dfs_low[u] = min(dfs_low[u], dfs_low[v])

    if dfs_low[u] == dfs_num[u]:
        scc_size = 0
        
        while True:
            v = st[-1]
            st.pop()
            visited[v] = False
            scc_size+=1 
            if u == v:
                max_scc_size = max(max_scc_size, scc_size)
                break
        
for u in range(n):
    if dfs_num[u] == -1:
        tarjanSCC(u)

print(n - max_scc_size)

                    

