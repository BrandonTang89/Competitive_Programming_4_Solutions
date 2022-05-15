'''
Kattis - oddgnome
theres probably a smarter way, but i really can't be bothered

Time: O(n^2 log n), Space: O(n)
'''
num_tc = int(input())
for _ in range(num_tc):
    arr = list(map(int, input().split()))
    n = arr.pop(0)
    
    for i in range(1, n):
        new_arr = arr[:i] + arr[i+1:]
        if new_arr == sorted(new_arr):
            print(i+1)
            break