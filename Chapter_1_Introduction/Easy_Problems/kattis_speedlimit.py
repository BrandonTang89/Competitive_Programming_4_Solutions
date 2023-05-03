'''
Kattis - speedlimit
Trivial
'''
while True:
    n = int(input())
    if n == -1: break
    speed, time = zip(*[map(int, input().split()) for _ in range(n)])
    time = [0] + list(time)
    time = [time[i] - time[i-1] for i in range(1, n+1)]
    
    print(sum([speed[i] * time[i] for i in range(n)]), "miles")