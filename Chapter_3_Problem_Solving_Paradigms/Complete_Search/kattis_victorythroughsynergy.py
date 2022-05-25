'''
Kattis - victorythroughsynergy
Just follow the question description. Pre-process a synergy matrix to determine the synergy
between 2 people in O(1) time. Then try all 10! permutations of players and check whether
the synergy of each node is >= its degree. If so, we have a valid permutation.

note that time actually TLE on my own computer, but somehow AC on judge so whatever.
Time: O(1), Space: O(1)
'''
e = int(input())
adjlist = [[] for i in range(10)]

for i in range(e):
    u, v = map(int, input().split())
    adjlist[u].append(v)
    adjlist[v].append(u)

players =  []
for i in range(0,10):
    name, country, league, team = input().split()
    players.append([country, league, team])

synergy_mat = [[0]*10 for i in range(10)]
for i in range(10):
    for j in range(10):
        if i == j:
            continue
        if players[i][2] == players[j][2]: # same team
            synergy_mat[i][j] += 2
            if players[i][0] == players[j][0]:
                synergy_mat[i][j] += 1
        
        elif players[i][1] == players[j][1]: # same league
            synergy_mat[i][j] += 1
            if players[i][0] == players[j][0]:
                synergy_mat[i][j] += 1
            
        elif players[i][0] == players[j][0]: # Same country
            synergy_mat[i][j] += 1

import itertools
for per in itertools.permutations([i for i in range(10)]):
	# Check whether the permutation is alright
    ok = True
    for pos in range(10):
        degree = len(adjlist[pos])
        player = per[pos]
        synergy = 0
        for adjpos in adjlist[pos]:
            adjplayer = per[adjpos]
            synergy += synergy_mat[player][adjplayer]
        if (synergy < degree):
            ok = False
            break
    if ok:
        print("yes")
        exit()
print("no")


        
        
        