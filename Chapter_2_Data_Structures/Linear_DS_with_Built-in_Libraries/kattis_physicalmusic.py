'''
Kattis - physicalmusic
One of those annoying problems that is "easy" but requires wrapping your head around the problem.
A single definitely has physical copies if "another song overtakes it after removing physical copies".
So we go from the end to the front, maintaining the minimum seen so far to see which songs have been
overtaken. Think about it with paper.

Time: O(n log n), Space: O(n) 
'''
tc = int(input())
for _ in range (tc):
    n = int(input())
    arr = [int(input()) - 1 for _ in range(n)]
    
    minSeen = n
    ans = []
    for i in range(n-1,-1,-1):
        if arr[i] > minSeen:
            ans.append(arr[i] + 1)
        minSeen = min(minSeen, arr[i])
    
    print(len(ans))
    print("\n".join(map(str, sorted(ans))))