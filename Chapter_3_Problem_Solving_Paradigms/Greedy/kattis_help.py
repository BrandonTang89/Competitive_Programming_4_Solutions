'''
Kattis - help
Consider the following strategy: give firm A the smallest amount, then for each remaining amount in descending
order, give to B then A then B, alternately until we are done. Observe that this strategy will not cause the
difference to be more than the initial smallest amount due to the fact that the largest amount will never be more
than twice that of the smallest amount. (take some time to consider this)

Time: O(n log n), Space: O(n)'''
while 1:
    n = int(input())
    if n == 0: break
    x = list(map(int, input().split()))
    x.sort(reverse=True)
    
    x.insert(0, x[-1])
    x.pop()
    
    for i in range(n):
        print(str(x[i]) + ('-A' if i%2==0 else '-B'), end=' ')
    print()