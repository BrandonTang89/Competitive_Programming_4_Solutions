''' Kattis - arbitrage
Refer to kattis_arbitrage.cpp for comments. 

Time: O(V^3), Mem: O(V^2)
'''
from sys import stdin, stdout
ans_string = ""
while (1):
    n = int(input())
    if n == 0:
        break
    currencies = stdin.readline().split()
    adjmat = {}
    for c in currencies:
        adjmat[c] = {}
        for k in currencies:
            if k != c:
                adjmat[c][k] = 0
            else:
                adjmat[c][k] = 1 # self loop should be 1

    e = int(stdin.readline())

    for _ in range(e):
        (a, b, rate) = stdin.readline().split()
        rate = rate.split(':')
        x = int(rate[1])/int(rate[0])
        adjmat[a][b] = max(adjmat[a][b], x)
    
    
    arbitrage = 0
    for k in currencies:
        for i in currencies:
            for j in currencies:
                adjmat[i][j] = max(adjmat[i][j], adjmat[i][k] * adjmat[k][j])
                if (adjmat[i][i] > 1):
                    arbitrage = 1
                    break
            if (arbitrage):
                break
        if (arbitrage):
            break

    if arbitrage:
        ans_string += "Arbitrage\n"
    else:
        ans_string += "Ok\n"

stdout.write(ans_string)
