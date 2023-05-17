'''
Kattis - compromise
2D array manipulation. Just take majority vote on each column.
Time: O(hw), Space: O(hw)
'''
tc = int(input())
for _ in range(tc):
    h, w = map(int, input().split())
    arr = [list(map(int, [c for c in input()])) for _ in range(h)]
    arr = list(map(list, zip(*arr)))
    
    for i in range(w):
        print(round(sum(arr[i])/len(arr[i])), end='')
    print()