'''
Kattis - minimumscalarproduct
This is an application of the rearrangement inequality. 

Time: O(n log n), Space: O(n)
'''
num_tc = int(input())
for tc in range(1, num_tc+1):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    a.sort()
    b.sort(reverse=True)

    ans = sum([a[i]*b[i] for i in range(n)])
    print(f"Case #{tc}: {ans}")