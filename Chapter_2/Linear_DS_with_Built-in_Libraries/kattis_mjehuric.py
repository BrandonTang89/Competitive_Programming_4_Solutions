'''
Kattis - mjehuric
Just simulate bubble sort. 

Time: O(n^2), Space: O(n)
'''
arr = list(map(int,input().split()))

s = sorted(arr)
while arr != s:
    for i in range(len(arr)-1):
        if arr[i] > arr[i+1]:
            arr[i], arr[i+1] = arr[i+1], arr[i]
            
            for i in arr:
                print(i, end=' ')
            print()