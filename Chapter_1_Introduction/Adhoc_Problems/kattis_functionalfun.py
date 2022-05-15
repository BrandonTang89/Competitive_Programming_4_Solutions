'''
Kattis - functionalfun
Actually not too difficult, just use something like an adjacency list.

Time / Space: O(n + len(domain) + len(codomain))
'''
from sys import stdin
lines = stdin.readlines()
line_index = 0
while line_index < len(lines):
    domain = lines[line_index].split()[1:]
    domain = {x: [] for x in domain}
    codomain = lines[line_index+1].split()[1:]
    codomain = {x: [] for x in codomain}
    line_index += 2
    
    n = int(lines[line_index])
    line_index += 1
    for i in range(n):
        line = lines[line_index]
        line_index += 1
        
        x, _ , y = line.split()
        domain[x].append(y)
        codomain[y].append(x)
    
    # Check if it is a function
    function = True
    for x in domain:
        if len(domain[x]) >= 2:
            function = False
            break
    if not function:
        print("not a function")
        continue
    
    # Check if it is a surjective function
    surjective = True
    for y in codomain:
        if len(codomain[y]) == 0:
            surjective = False
            break
    
    # Check if it is injective
    injective = True
    for y in codomain:
        if len(codomain[y]) >= 2:
            injective = False
            break
    
    if injective and surjective:
        print("bijective")
    elif injective:
        print("injective")
    elif surjective:
        print("surjective")
    else:
        print("neither injective nor surjective")