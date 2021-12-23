'''
kattis - competitivearcadebasketball
Relatively simple problem. Just ensure we don't declare the same person the winner multiple times.

Time: O(m), Space: O(n)
'''
n, p, m = map(int, input().split())
scores = {}

for i in range(n):
    name = input()
    scores[name] = 0

for i in range(m):
    name, score = input().split()
    score = int(score)
    
    if (scores[name] != -1):
        scores[name] += score
        if (scores[name] >= p):
            print(f"{name} wins!")
            scores[name] = -1

for i in scores:
    if (scores[i] == -1):
        break
else:
    print("No winner!")