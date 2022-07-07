'''
Kattis - trip2007
Assume we are trying to make k bags at the end. Observe that we should take the largest k bags as the outermost
bags. Now consider the strategy of putting the next largest k bags, in decreasing order of size into the existing
bags. E.g. If we have 1 1 2 2 2 3 -> we take (3, 2, 2) as the outer bags and then make (3 2, 2 1, 2 1). We repeat
this patterun until we are done with all the bags.

Observe that as long as k >= max_frequency, this strategy will be gauranteed to work. Also observe that we cannot
possibly do better than k = max_frequency because by pigeon hole principle, this causes 2 bags of the same size
to be fitted into the same piece. Thus this strategy produces the least number of pieces possible. Observe that
since we rotate between bags, the number of bags within each piece is also minimised. Thus this strategy is
indeed optimal.


Time: O(n log n), Space: O(n)'''
from collections import Counter
while 1:
    n = int(input())
    if (n == 0):
        break
    arr = list(map(int, input().split()))
    k = max(Counter(arr).values())

    print(k)
    arr.sort(reverse=True)
    for i in range(k):
        for j in arr[i::k]:
            print(j, end=' ')
        print()
