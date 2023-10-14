'''
Katis - canvasline
Greedy/construction. Processing the canvases from left to right, it is always optimal to put a peg
on the right edge of the canvas intersecting the next canvas if both the current and next canvas require
>= 1 pegs more. (This is obvious by exchange argument)

Time: O(np), Space: O(n)
'''
n = int(input())

sheets = [tuple(map(int, input().split())) for _ in range(n)]

numpegs = [0] * n

numexisting = int(input())
existingpegs = set(map(int, input().split()))

for i in range(n):
    for peg in existingpegs:
        if sheets[i][0] <= peg <= sheets[i][1]:
            numpegs[i] += 1
    if (numpegs[i] > 2):
        print("impossible")
        exit()
ans = 0
pegs = []
for i in range(n-1):
    if numpegs[i] < 2:
        ans += 1
        numpegs[i] += 1
        if sheets[i][1] == sheets[i+1][0] and numpegs[i+1] < 2 and sheets[i][1] not in existingpegs:
            numpegs[i+1] += 1
            pegs.append(sheets[i][1])
        else:
            for j in range(sheets[i][0]+1, sheets[i][1]):
                if j not in existingpegs:
                    pegs.append(j)
                    existingpegs.add(j)
                    break

    if numpegs[i] < 2:
        ans += 1
        numpegs[i] += 1
        for j in range(sheets[i][0]+1, sheets[i][1]):
            if j not in existingpegs:
                pegs.append(j)
                existingpegs.add(j)
                break

if numpegs[-1] < 2:
    ans += (2 - numpegs[-1])
    for j in range(sheets[-1][0]+1, sheets[-1][1]):
        if j not in existingpegs:
            pegs.append(j)
            existingpegs.add(j)
            numpegs[-1] += 1
            if numpegs[-1] == 2:
                break

for i in range(n):
    assert numpegs[i] == 2
print(ans)
print(" ".join(map(str, pegs)))
