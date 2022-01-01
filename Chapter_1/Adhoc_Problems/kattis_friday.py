'''
Kattis - friday
Do some modular arithmetic to determine whether friday falls on the 13th of a particular month,
it depends on the first day of the month. Also note that some months have less than 13 days.

Time: O(m), Space: O(m)
'''
num_tc = int(input())
for tc in range(num_tc):
    D, m = map(int, input().split())
    st = 0
    days = input().split()
    days = [int(x) for x in days]
    
    ans = 0
    st = 0
    for x in days:
        if x >= 13:
            ans += ((st + 13) % 7 == 6)
        st = (st + x) % 7
    
    print(ans)