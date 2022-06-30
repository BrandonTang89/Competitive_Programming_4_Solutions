'''
Kattis - pripreme
Sort the numbers in increasing order. Let the first dude teach from the last element and the second dude teach
from the second last element. Both teach in decreasing order. The first dude will be at least as slow as the second
dude at every stage, so the first dude will always be behind the second dude. Once the second dude finishes the 
lowest number, he just finishes the largest number, which might still be limited by the first dude. First dude takes
sum(A) time, second takes sum(A) + max(0, A[-1] - sum(A[:-1])) time!

Time: O(n log n), Space: O(n)'''
n = int(input())
A = list(map(int, input().split()))
A.sort()

ans = sum(A) + max(0, A[-1] - sum(A[:-1]))
print(ans)
