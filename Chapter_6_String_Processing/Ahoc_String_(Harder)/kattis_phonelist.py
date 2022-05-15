'''
Kattis - phonelist
The key observation is that if we sort the numbers lexicographically, if a number A is a prefix
of another number B, then A will be directly before B (assuming there is no other number C such that
A is a prefix of C which is a prefix of B).

Time: O(n log n), Space: O(n)
'''
num_tc = int(input())

for _ in range(num_tc):
    n = int(input())
    arr = []
    for _ in range(n):
        arr.append(input())
    
    yes = True
    arr.sort()
    for i in range(n - 1):
        if (arr[i + 1].startswith(arr[i])):
            yes = False
            break
    print("YES" if yes else "NO")