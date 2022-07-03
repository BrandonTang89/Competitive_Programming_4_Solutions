'''
Kattis - playground
Observe that if we need to use all wires, we can make a simple closed shape on the 2D plane if and only if the
sum of the diameters of the wires apart from the longest one is >= the diameter of the longest wire (something
like triangular inequality). Now, since we don't need to use all the wires, we can try assuming the kth wire
is the longest wire for all k from 0 to n-1.

Time: O(n^2), Space: O(n)'''
while 1:
    n = int(input())
    if n == 0:
        break
    arr = list(map(lambda x: int(float(x)*1000 + 0.3), input().split())) # Avoid floating point issues
    arr.sort()

    while (len(arr) != 0):
        if arr[-1] <= sum(arr[:-1]):
            print("YES")
            break
        else:
            arr.pop()
    else:
        print("NO")
