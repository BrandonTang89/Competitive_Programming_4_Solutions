'''
Kattis - height
Insertion sort simulation, just figure it out.

Time: O(n^2), Space: O(n)
'''
num_tc = int(input())
for tc in range(1, num_tc+1):
    arr = input().split()
    arr = [int(x) for x in arr]
    arr.pop(0)
    
    ans = 0
    
    for i in range(len(arr)-1):
        for j in range(i+1, 0, -1):
            if arr[j] < arr[j-1]:
                arr[j], arr[j-1] = arr[j-1], arr[j]
                ans+= 1 
            else:
                break
    print(tc, ans)