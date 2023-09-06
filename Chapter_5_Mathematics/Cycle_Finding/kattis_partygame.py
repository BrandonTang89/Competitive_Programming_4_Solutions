'''
Kattis - partygame
Notice that the graph of edges (current person number -> card held by that person) forms a
1-degree out and 1-degree in graph, i.e. a bunch of disjoint cycles. Observe that the game will
end if and only if all cycles are powers of 2, else we will eventually reach a cycle of odd length
that will never shrink. Just DFS to count the length of each cycle and check if they are all powers
of 2 by seeing if they have exactly 1 bit on in binary.

Time: O(n), Space: O(n)
'''
tc = int(input())


def bitsoncount(x):
    return bin(x).count('1')


cur = 0
for _ in range(tc):
    n = int(input())
    out = list(map(lambda x: int(x)-1, input().split()))
    done = [False for _ in range(n)]
    cycles = []

    def dfs(u):
        global cur
        done[u] = True
        cur += 1
        if (done[out[u]]):
            cycles.append(cur)
            return
        dfs(out[u])

    for i in range(n):
        if (done[i]):
            continue
        cur = 0
        dfs(i)

    if all(map(lambda x: bitsoncount(x) == 1, cycles)):
        print("All can eat.")
    else:
        print("Some starve.")
