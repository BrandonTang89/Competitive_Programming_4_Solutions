'''
Kattis - succession

Since the nodes are strings with very sketchy input formatting and the number of nodes is small,
we use python to make coding easier. Also, python will natively handle floating point numbers,
so we don't have to worry about making the founder have large royal blood value or other workarounds
that one would have to do in C++.

The central idea here is to use kahn's algorithm to process nodes from top down, processing the nodes
that have 0 in degree first. Nodes that have 0 in degree would have no other parents to give them
royal blood, so we can safely propagate half of their royal blood to their children. Afterwards,
we reduce the in-degree of the child by 1 since this parent has already given them the blood.

Time: O(V + E), Mem: O(V + E)
'''
(n, m) = input().split()
n = int(n)
m = int(m)
founder = input()
adjlist = {}
royal_blood = {founder: 1}
in_degree = {founder: 0}

for i in range(n):
    child, p1, p2 = input().split()
    if not p1 in adjlist:
        adjlist[p1] = set()
    if not p2 in adjlist:
        adjlist[p2] = set()
    if not child in adjlist:
        adjlist[child] = set()


    if not p1 in in_degree:
        in_degree[p1] = 0
    if not p2 in in_degree:
        in_degree[p2] = 0
    if not child in in_degree:
        in_degree[child] = 0

    adjlist[p1].add(child)
    adjlist[p2].add(child)
    in_degree[child]+= 2

q = []
for person, in_deg in in_degree.items():
    if in_deg == 0:
        q.append(person)

while (not (len(q) == 0)):
    c = q[0]
    q.pop(0)

    if (not c in royal_blood):
        royal_blood[c] = 0
    
    for child in adjlist[c]:
        if (not child in royal_blood):
            royal_blood[child] = 0
        
        royal_blood[child] += (royal_blood[c]/2)
        in_degree[child] -=1

        if in_degree[child] == 0:
            q.append(child)
        
    
# print(royal_blood)
max_royal = 0
royal_winner = "no one"
for i in range(m):
    contestant = input()
    if (not contestant in royal_blood):
        royal_blood[contestant] = 0

    if royal_blood[contestant] > max_royal:
        max_royal = royal_blood[contestant]
        royal_winner = contestant

print(royal_winner)