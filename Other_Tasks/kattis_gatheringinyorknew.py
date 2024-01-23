'''
Kattis - gatheringinyorknew
Greedy + Static Range Sum
An easyish problem but perhaps prone to bugs if we don't reason carefully.

The first observation is that one end of the portal should be at yorknew. This is because for any
given portal positions, we can always move the portal that is nearer to yorknew to yorknew and we can only
improve the arrangement since the set of people choosing to go directly to yorknew are unaffected by people
using the portal will save time

The second observation is that we can choose to deal with the positive and negative people separately.
For the side without the portal, everyone just walks directly to yorknew. For the side with the portal,
people will walk to the nearer of {yorknew, portal}.

The third observation is that the portal will be at the position of some person. This is because if the portal
were between 2 people, we can improve the arrangement by moving the portal to the side with more people (think
about it, it works). If the number of people on both sides are equal, we can move the portal to either side and
still achieve an equally optimal arrangement.

Now, the idea is to try all possible portal positions from left to right, assuming we only deal with the positive
axis. People along the axis can be divided into 3 categories, the ones that will just move to the left, the ones
that will move right into the right end of the portal, and the ones that will move left into the right end of the
portal. These 3 will be partitioned by a boundary position (b) and the portal position. 

The boundary position is defined by the fact that all people with index < b will go directly to the left, and all
people with index >= b will go to the portal.  People with index > the index of the person the portal is at will
go left to get into the portal.

The key observation at this stage is that b will only shift right as the portal moves right. As such, the total
cost of moving b across all portal positions is O(n) (amortized O(1) per portal position). As such, we can just
use a while loop to find the optimal b for each portal position.

With a found value of b, we can compute the cost of the arrangement with some simple math and using a precomputed
static range sum.

We find the minimum cost with the portal position in both the positive and negative axis and take the best answer.

Time: O(n log n), Space: O(n)
'''
n = int(input())
arr = list(map(int, input().split()))
arr1 = list(filter(lambda x: x > 0, arr))
arr2 = list(filter(lambda x: x < 0, arr))
arr2 = list(map(lambda x: -x, arr2))

s1 = sum(arr1)
s2 = sum(arr2)

def f(arr):
    arr.sort()
    n = len(arr)
    prefix = [0] * (n + 1) # prefix[i] = sum(arr[:i])
    for i in range(1, n + 1):
        prefix[i] = prefix[i - 1] + arr[i - 1]
        
    def rangeSum(i, j): # sum(arr[i:j])
        return prefix[j] - prefix[i]
    
    mini = rangeSum(0, n)
    # all people < b will go directly to the left
    # b .. i will go to the portal rightwards
    # i+1 .. will go to the portal leftwards
    b = 0
    for i in range(n):
        # suppose the portal is at arr[i]
        c = arr[i]
        while b < n and c - arr[b] > arr[b]:
            b += 1
        # now c - arr[b] <= arr[b] so b will rather go right to the portal
        
        cur = rangeSum(0, b) + (c*(i - b + 1) - rangeSum(b, i + 1)) + (rangeSum(i + 1, n) - c*(n - i - 1)) # current cost
        mini = min(mini, cur)
        
    return mini

print(min(s1 + f(arr2), s2 + f(arr1)))