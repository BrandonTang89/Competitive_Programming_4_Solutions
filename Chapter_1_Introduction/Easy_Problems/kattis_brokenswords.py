'''
Kattis - brokenswords
Simple.
Time: O(n), Space: O(1)
'''
n = int(input())
arr = [0, 0]
for _ in range(n):
    x = input()
    arr[0] += (x[0] == '0') + (x[1] == '0')
    arr[1] += (x[2] == '0') + (x[3] == '0')
    
num = min(arr)//2
print(num, arr[0] - num*2, arr[1] - num*2)