
def diff(arr):
    ans = [arr[i+1] - arr[i] for i in range(len(arr)-1)]
    return ans

for _ in range(int(input())):
    n = int(input())
    arr = [int(x) for x in input().split()]
    
    best = sum(arr)
    while len(arr) > 1:
        arr = diff(arr)
        best = max(best, sum(arr))
        best = max(best, -sum(arr))
    
    print(best)
    