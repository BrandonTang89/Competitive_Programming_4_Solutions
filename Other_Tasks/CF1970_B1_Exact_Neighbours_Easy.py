'''
CF1970 B1
Since the distances are even, we can just put all the houses along the main diagonal.
We put the houses with largest distances furthest from the middle, greedily.

We should show that this doesn't work then it would be always impossible.. Proof seems non-trivial though.
'''
n = int(input())
distances = list(map(int, input().split()))
distances = [(x//2, i) for (i, x) in enumerate(distances)]
distances.sort(reverse=True)
arrangedFirst = []
arrangedSecond = []

for (i, distance) in enumerate(distances):
    if i % 2 == 0:
        arrangedFirst.append(distance)
    else:
        arrangedSecond.append(distance)

arranged = arrangedFirst + arrangedSecond[::-1]

matches = [-1] * n
pos = [(0, 0) for _ in range(n)]

for i in range(n):
    dist, idx = arranged[i]
    pos[idx] = (i+1, i+1)
    left = i-dist
    right = i+dist
    matchedWith = None
    if left >= 0:
        matchedWith = arranged[left][1]
    if right < n:
        matchedWith = arranged[right][1]
        
    if matchedWith is None:
        print("NO")
        exit()
    matches[idx] = matchedWith
    
print("YES")
for i in range(n):
    print(pos[i][0], pos[i][1])
    
for i in range(n):
    print(matches[i]+1, end=" ")
print()