'''
Kattis - manacala
Somewhat like a constructive problem. The principle is that given a currently winning board,
we can do a linear scan for the first empty slot then we increase it by the value of its index
and decrement all the earier slots by 1. This creates a winning board of the next value.

We pre-compute the values and then refer to them when answering the queries.

Time: O(1), Space: O(1)'''
archive = [[]]
ans = [0]
ans[0] = -1 
for b in range(1, 2001):
    # Find first empty slot
    fes = -1
    for i in range(1, len(ans)):
        if ans[i] == 0: 
            fes = i
            break
    if fes == -1:
        ans.append(0)
        fes = len(ans) - 1
    
    # print("fes ", fes)
    for i in range(1, fes):
        ans[i]-=1
    ans[fes] += fes
    
    archive.append(ans[1:])

num_tc = int(input())
for tc in range(1,num_tc+1):
    _, n = map(int, input().split())
    
    li = archive[n]
    composite_list = [li[x:x+10] for x in range(0, len(li),10)]
    
    print(tc, len(li))
    for l in composite_list:
        print(" ".join(map(str, l)))