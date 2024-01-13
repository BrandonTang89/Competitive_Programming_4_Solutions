'''
Kattis - houselawn
Straightforward question. Just remember to stable sort with the key as the price for all acceptable mowers.

Time: O(m log m), Space: O(m)
'''
l, m = map(int, input().split())

weekTime = 10080
acceptable = []

for _ in range(m):
    name, p, c, t, r = input().split(',')
    p, c, t, r = map(int, (p, c, t, r))
    
    areaPerCut = c * t
    cutTime = t + r
    numCuts = weekTime / cutTime
    areaPerWeek = numCuts * areaPerCut
    if areaPerWeek >= l:        
        acceptable.append((p, name))
        

if len(acceptable) == 0:
    print("no such mower")
else:
    acceptable.sort(key=lambda x: x[0])
    minPrice = acceptable[0][0]
    acceptable = [x[1] for x in acceptable if x[0] == minPrice]
    for name in acceptable: print(name)