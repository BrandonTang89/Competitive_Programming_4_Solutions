'''
Kattis - cake
Constructive problem: We can actually always cut the cake with 0 leftover. The strategy is to go row by row, column by column
and if there is a rose in our position, we cut it out together with anything to the left or top of it. For the last rose on a row,
we cut everything to the left right and top of it. For the last row that contains a rose, we cut everything to the left top and bottom
of each rose. The corner case of the last rose on the last row is basically taking the rest.

Time: O(n log n + hw), Space: O(n)
'''
h, w, n = map(int, input().split())

roses = [map(int, input().split()) for _ in range(n)]
roses = [(r, c) for r, c in roses]
roses.sort()

prevrow = 0
currow = 1
lastrow = roses[-1][0]

while True:
    rosesThisRow = []
    while (len(roses) > 0 and roses[0][0] == currow):
        rosesThisRow.append(roses.pop(0))
    hasRoses = (len(rosesThisRow) > 0)

    prevCol = 0
    while len(rosesThisRow) > 1:
        print(
            f"{prevrow+1} {prevCol+1} {h if currow == lastrow else currow} {rosesThisRow[0][1]}")
        prevCol = rosesThisRow[0][1]
        rosesThisRow.pop(0)

    if len(rosesThisRow) == 1:
        print(f"{prevrow+1} {prevCol+1} {h if currow == lastrow else currow} {w}")

    if hasRoses:
        prevrow = currow

    if currow == lastrow:
        break
    currow += 1

print(0)
