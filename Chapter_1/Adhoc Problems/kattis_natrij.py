'''
Kattis - Natrij
A basic but rather annoying time-based problem.
Beware of the corner case where time_now == time_at_explosion --> ans = 24h

Time: O(1), Mem: O(1)
'''
import datetime
time_now = input()
time_at_explosion = input()

time_now = time_now.split(":")
time_now = [int(i) for i in time_now]
time_now = datetime.datetime(2021,1,1,time_now[0], time_now[1], time_now[2])
time_now = time_now

time_at_explosion = time_at_explosion.split(":")
time_at_explosion = [int(i) for i in time_at_explosion]
time_at_explosion = datetime.datetime(2021,1,1,time_at_explosion[0], time_at_explosion[1], time_at_explosion[2])

ans = (time_at_explosion - time_now)
# Adjust for time at explosion being "before" time now
if (ans < datetime.timedelta(days=0)):
    ans += datetime.timedelta(days=1)
ans = str(ans).split(':')

# Correct for ensuring 0 before the hour
ans_again = []
for i in ans:
    if len(i) == 1:
        i = '0' + i
    
    ans_again.append(i)

# Corner Case
ans_again = ":".join(ans_again)
if ans_again == "00:00:00":
    ans_again = "24:00:00"

print(ans_again)