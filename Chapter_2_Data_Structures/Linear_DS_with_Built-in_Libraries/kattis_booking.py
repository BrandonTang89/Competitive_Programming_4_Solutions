'''
Kattis - booking
Really counting on the datatime library to carry us for this question. Once we can easily compare times and add time deltas,
the rest is really quite easy. Just sort in increasing start datetime, then reuse rooms as much as possible, it doesn't
matter which room is reused. 
Time: O(n log n), Space: O(n)
'''
import datetime
for _ in range(int(input())):
    n, c = map(int, input().split())
    cleaningTime = datetime.timedelta(minutes=c)
    bookings = []
    for _ in range(n):
        uid, startDate, startTime, endDate, endTime = input().split()
        startDateTime = datetime.datetime.strptime(startDate + " " + startTime, "%Y-%m-%d %H:%M")
        endDateTime = datetime.datetime.strptime(endDate + " " + endTime, "%Y-%m-%d %H:%M")
        bookings.append((startDateTime, endDateTime))
    bookings.sort(key=lambda x: x[0])
    rooms = []
    for (startDateTime, endDateTime) in bookings:
        for i in range(len(rooms)):
            if rooms[i] <= startDateTime:
                rooms[i] = endDateTime + cleaningTime
                break
        else:
            rooms.append(endDateTime + cleaningTime)
    print(len(rooms))