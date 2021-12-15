'''
Kattis - icpcteamselection
Notice that the bottom 1/3 of people should spread themselves out amongst all the teams to act as the
worst player for each team. After that, the top 2 people should join the first team, the second best 2
join the second team, etc until we are done.

Time: O(n log n), Space: O(n)
'''
num_tc = int(input())
for _ in range(num_tc):
    n = int(input())
    n *= 3 
    arr = list(map(int, input().split()))
    arr.sort(reverse=True)
    arr = arr[:2*n//3]
    
    ans = 0
    for i, e in enumerate(arr):
        if (i%2):
            ans += e
    print(ans)