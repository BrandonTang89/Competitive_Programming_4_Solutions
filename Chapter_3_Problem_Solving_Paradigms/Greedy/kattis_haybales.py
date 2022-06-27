'''
Kattis - haybales
Consider a good move being a move that moves all 3 of the haybales selected (110 -> 011 and 100 -> 001). Consider
bad moves being moves that only move 2 of the haybales selected (e.g. 010 -> 001). Obviously we don't do moves 
that move nothing. Observe that we should always do good moves whenever possible, doing bad moves only if we
can't find a good move, we stop once the array is sorted.

Time: O(n^2), Space: O(n)
'''
arr = [1 if x == 'P' else 0 for x in input()]
sarr = sorted(arr)
ans = 0
while (arr != sarr):
    # print(arr)
    good_move = False
    for i in range(0, len(arr)-2):
        if arr[i] != 0 and arr[i+2] != 1 and not (arr[i] == arr[i+1] and arr[i+1] == arr[i+2]):
            num_ones = arr[i] + arr[i+1] + arr[i+2]
            for j in range(i+2, i+2-num_ones-1, -1):
                arr[j] = 1
            for j in range(i, i+3-num_ones):
                arr[j] = 0
            good_move = True
            ans += 1
    if not good_move:
        for i in range(0, len(arr)-1):
            if arr[i] == 1 and arr[i+1] == 0:
                arr[i] = 0
                arr[i+1] = 1
                ans += 1
                break

print(ans)
