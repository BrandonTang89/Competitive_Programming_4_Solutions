'''
Kattis - flagquiz
Relatively straightforward, for each alternative i, we compare against all other alternatives to
find the max_num_changes for i. We keep track of the smallest max num changes and keep a list
of the indices and print the list at the end.

Note the use of the various python specific things to make life easier (especially zip, split and join)

Time: O(n^2 * num_parts), Space: O(n*num_parts)
'''
n = input()
n = int(input())
A = []
for _ in range(n):
    A.append(list(input().split(',')))

ans = []
smallest_max_num_changes = 200
for i in range(n):
    max_num_changes = 0
    for j in range(n):
        # Compare A[i] with A[j]
        num_changes = 0 
        for (a, b) in zip(A[i], A[j]):
            if (a != b):
                num_changes += 1
        max_num_changes = max(num_changes, max_num_changes)
    
    if (max_num_changes == smallest_max_num_changes):
        ans.append(i)
    elif (max_num_changes < smallest_max_num_changes):
        smallest_max_num_changes = max_num_changes
        ans = [i]

for i in ans:
    print(','.join(A[i]))