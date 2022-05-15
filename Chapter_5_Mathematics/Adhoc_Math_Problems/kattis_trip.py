'''
Kattis - trip
This may be a bit confusing, but the key observation is that each person can have at most 1 extra cent
than another person. But who should have the extra cents? Well, people who had more money than the
average initially should have the extra cent! It doesn't make sense to give the extra money to people
who had less money initially, because more money would have to be transferred to them to get that.

So, first we determine the number of cents that can be equally divided among all. This divided by 
the number of people gives the average.
Then, we determine the "extra" cents that we have left undivided. For each person with more money than
the average, we give away all until they have the average, but we "return" them the extra cent if there
are still extra cents left.

We don't have to bother about people with less than the average amount of money since by conservation
of money, the amount of money given away is equal to the amount of money transferred which is equal to 
the amount of money received. We are thus able to only considere amount of money given away and ignore
the amount of money received.

Time: O(n), Space: O(n)
'''
while True:
    x = int(input())
    if (x == 0):
        break
    
    # Costs in cents
    costs = []
    for i in range(x):
        costs.append(int(float(input()) * 100 + 0.5)) # + 0.5 to round to avoid floating point errors
    
    s = sum(costs)
    extra = 0
    while (s % x != 0):
        s -= 1
        extra += 1
    ave = s // x

    total = 0
    for i in range(x):
        if (costs[i] > ave):
            total += costs[i] - ave
            if (extra > 0):
                total -= 1
                extra -= 1
    
    total /= 100
    print("$%.2f" % total)