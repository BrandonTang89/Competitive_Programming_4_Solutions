'''
Kattis - longswaps
The stuff within s[len(s)-k:k] cannot be moved so they must be correct to begin with. The rest can be proved to be sortable
by construction of a sorting algorithm (sort the non-edge stuff by swap to either left or right wall then move into the
correct position. Finish by perhaps swapping the left and right edge).
Time: O(n log n), Space: O(n)
'''
s, k = input().split()
k = int(k)
s = list(s)
print("Yes" if sorted(s)[len(s)-k:k] == s[len(s)-k:k] else "No")
