'''
Kattis - vote
Sort and determine the sum.

Time: O(n log n), Space: O(n) {can be done in O(n) since only top 2 are impt}
'''
num_tc = int(input())
for tc in range(num_tc):
    n = int(input())
    arr = [(int(input()), i+1) for i in range(n)]
    arr.sort()
    total = sum([arr[x][0] for x in range(n)])
    
    if arr[n-1][0] == arr[n-2][0]:
        print("no winner")
    else:
        if arr[n-1][0] > total/2:
            print("majority winner", arr[n-1][1])
        else:
            print("minority winner", arr[n-1][1])