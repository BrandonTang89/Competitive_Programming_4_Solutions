'''
Kattis - chanukah
Just triangle numbers + n

Time: O(1), Space: O(1)'''
tc = int(input())
for t in range(tc):
    _, n = map(int, input().split())
    print(t+1, n + (n+1)*(n)//2)